#include "TileMapLoader.h"
#include "TileMap.h"
#include "map_io.h"
#include "Log.h"

TileMapLoader::TileMapLoader(TileMap* pMap) : m_pMap(pMap),ResBase(0,ResType_Img,"")
{

}

TileMapLoader::~TileMapLoader()
{

}


void TileMapLoader::reset(vector<TileInfo*>& tiles,vector<MapMaskInfo*>& masks)
{
	m_vTiles.clear();
	// 找出需要绘制的tiles中包含的mask信息
	for (size_t i = 0; i < tiles.size(); ++i)
	{
		TileInfo* pTile = tiles[i];
		pTile->flag = TileFlagLoading;

		TileInfoAsync* pInfo = new TileInfoAsync;
		pInfo->tag = pTile->tag;
		pInfo->img = NULL;
		m_vTiles.push_back(pInfo);
	}

	m_vMasks.clear();
	// 找出需要绘制的tiles中包含的mask信息
	for (size_t i = 0; i < masks.size(); ++i)
	{
		MapMaskInfo* pMask = masks[i];
		pMask->flag = TileFlagLoading;

		MaskInfoAsync* pInfo = new MaskInfoAsync;
		pInfo->tag = pMask->tag;
		pInfo->mask_data_size = pMask->mask->mask_data_size;
		pInfo->relate_data_size = pMask->mask->relate_data_size;
		pInfo->mask_relation = NULL;
		pInfo->img = NULL;
		m_vMasks.push_back(pInfo);
	}
}

void TileMapLoader::loadTileImages()
{
	int tx = 0;
	int ty = 0;

	for ( size_t i = 0;i<m_vTiles.size();++i )
	{
		Data data = map_io::read_image_data(m_pMap->getMapFileName().c_str(),m_vTiles[i]->tag,m_pMap->getMapContext());
		Image* pImage = new Image;
		if ( pImage && pImage->initWithImageData(data.getBytes(),data.getSize()))
		{
			m_vTiles[i]->img = pImage;
			continue;
		}
		CC_SAFE_DELETE(pImage);
		m_vTiles[i]->img = NULL;
	}
}

void TileMapLoader::loadMaskImages()
{
	for ( size_t i = 0;i<m_vMasks.size();++i )
	{
		Data data = map_io::read_mask_image_data(m_pMap->getMapFileName().c_str(),m_vMasks[i]->tag,m_pMap->getMapContext());

		assert(data.getSize() == m_vMasks[i]->mask_data_size);
		// 将遮挡关系数据拷贝出来,
		//relate_data_size也包含遮挡物的mask数据，前半部分是遮挡关系数据，后半部分是遮挡物的mask数据
		// 就让他先包含这些数据
		assert(m_vMasks[i]->mask_relation == nullptr);
		m_vMasks[i]->mask_relation = new unsigned char[m_vMasks[i]->relate_data_size];
		memcpy(m_vMasks[i]->mask_relation,data.getBytes(),m_vMasks[i]->relate_data_size);

		// 生成遮挡图片数据
		// modified by wenzy
		/*
		Image* pImage = new Image;
		if ( pImage && pImage->initWithImageData(data.getBytes()+m_vMasks[i]->mask->relate_data_size,data.getSize()-m_vMasks[i]->mask->relate_data_size))
		{
			m_vMasks[i]->img = pImage;
			continue;
		}
		CC_SAFE_DELETE(pImage);
		m_vMasks[i]->img = NULL;
		*/

		m_vMasks[i]->img = fillMaskImageByMask(data,m_vMasks[i]);
	}
}

// add by wenzy
Image* TileMapLoader::fillMaskImageByMask(Data &data,MaskInfoAsync* pMask)
{
	struct timeval now1;
	struct timeval now2;
	struct timeval now3;
	
	gettimeofday(&now1, NULL);

	Image* pImage = new Image;
	if ( pImage && pImage->initWithImageData(data.getBytes()+pMask->relate_data_size,
		data.getSize()-pMask->relate_data_size) )
	{
		gettimeofday(&now2, NULL);
		float fDeltaTime = (now2.tv_sec - now1.tv_sec) * 1000 + (now2.tv_usec - now1.tv_usec) / 1000.0f;

		int idx = 0;
		int len = pImage->getWidth()*pImage->getHeight();
		unsigned char* pixels_new = new unsigned char[len*4];
		if(pixels_new)
		{
			memset(pixels_new,0,len*4);

			unsigned char* pSrc = pImage->getData();
			unsigned char* pTarget = pixels_new;
			//relate_data_size也包含遮挡物的mask数据，前半部分是遮挡关系数据，后半部分是遮挡物的mask数据
			unsigned char* mask = pMask->mask_relation;
			mask += pMask->relate_data_size/2;//skip to 遮挡物的mask数据
			int nFillBits = 0;
			unsigned char maskByte = *mask;
			
			for ( int i = 0;i<len;++i )
			{	
				if (  ((1 << nFillBits) & maskByte)  == 0) 
				{
					pSrc += 3;
					pTarget += 4;
				}
				else
				{
					*pTarget++ =  *pSrc++;
					*pTarget++ =  *pSrc++;
					*pTarget++ =  *pSrc++;
					*pTarget++ = 255;
				}	
				++nFillBits;
				if(nFillBits == 8)
				{
					++mask;
					maskByte = *mask;
					nFillBits = 0;
				}
			}
			
			Image* ret = new Image;
			if ( ret && ret->initWithRawData(pixels_new,len*4, pImage->getWidth(),pImage->getHeight(),8))
			{
				delete [] pixels_new;
				CC_SAFE_DELETE(pImage);

				gettimeofday(&now3, NULL);
				float fDeltaTime2 = (now3.tv_sec - now1.tv_sec) * 1000 + (now3.tv_usec - now1.tv_usec) / 1000.0f;

				return ret;
			}

			delete [] pixels_new;
			CC_SAFE_DELETE(ret);
		}
	}

	CC_SAFE_DELETE(pImage);

	return NULL;
}


bool TileMapLoader::load()
{
	loadTileImages();
	loadMaskImages();
	return true;
}

void TileMapLoader::refreshTiles()
{
	int x,y;

	// 更新TILE
	for ( size_t i = 0;i<m_vTiles.size();++i )
	{
		TileInfoAsync* pInfo = m_vTiles[i];
		if ( pInfo->img )
		{
			Texture2D* pTexture = new Texture2D();
			if( pTexture && pTexture->initWithImage(pInfo->img) )
			{
				Rect rect = Rect::ZERO;
				rect.size = pTexture->getContentSizeInPixels();

				ShaderSprite* pSprite = NULL;
				if ( m_pMap->getGrey() )
				{
					pSprite = ShaderSprite::createWithTexture(pTexture,rect,-1.0f);
				}
				else
				{
					pSprite = ShaderSprite::createWithTexture(pTexture,rect,1.0f);
				}
				
				if ( pSprite )
				{
					TileInfo* pTile = m_pMap->getTileMgrNear()->getTile(pInfo->tag);
					pTile->spr = pSprite;
					pTile->flag = TileFlagShowing;
					m_pMap->getTileMgrNear()->index2Tile(pTile->tag,x,y);
					m_pMap->getTileMgrNear()->tile2World(x,y);
					pSprite->setAnchorPoint(Point(0,0));
					pSprite->setPosition(Point(x,y));
					m_pMap->getTerrainLayer()->addChild(pSprite,0,pTile->tag);
				}
			}

			CC_SAFE_RELEASE(pTexture);
		}
	}
}

void TileMapLoader::refreshMasks()
{
	for ( size_t i = 0;i<m_vMasks.size();++i )
	{
		MaskInfoAsync* pInfo = m_vMasks[i];
		if ( pInfo )
		{
			MapMaskInfo* pMaskInfo = m_pMap->getMask(pInfo->tag);
			MapMask* pMask = MapMask::createWithMaskInfo(pMaskInfo,pInfo->img,m_pMap->getGrey());
			if ( pMask )
			{
				pMaskInfo->obj = pMask;
				pMaskInfo->flag = TileFlagShowing;
				assert(pMaskInfo->mask_relation == nullptr);
				pMaskInfo->mask_relation = new unsigned char[pInfo->relate_data_size];
				memcpy(pMaskInfo->mask_relation,pInfo->mask_relation,pInfo->relate_data_size);
				// 处理遮挡物件进地图
				pMask->EnterMap(m_pMap,Point(pMaskInfo->mask->x,pMaskInfo->mask->y));
			}
		}
	}
}
/*
void TileMapLoader::mask2World(map_mask *pMask,int &x,int &y)
{
	int mapHeight = m_pMap->getMapHeight();
	x = pMask->x;
	y = pMask->y+pMask->h;
	y = mapHeight - y;
}
*/


void TileMapLoader::onLoadComplete(ResTask* pTask)
{
	if( pTask->result == ResResult_Ok )
	{
		refreshTiles();
		refreshMasks();
	}

	for ( size_t i = 0;i<m_vTiles.size();++i )
	{
		CC_SAFE_DELETE(m_vTiles[i]->img);
		CC_SAFE_DELETE(m_vTiles[i]);
	}
	m_vTiles.clear();
	for ( size_t i = 0;i<m_vMasks.size();++i )
	{
		CC_SAFE_DELETE(m_vMasks[i]->img);
		CC_SAFE_DELETE(m_vMasks[i]->mask_relation);
		CC_SAFE_DELETE(m_vMasks[i]);
	}
	m_vMasks.clear();

	ResBase::onLoadComplete(pTask);

	delete this;
}