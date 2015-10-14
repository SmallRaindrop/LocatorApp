/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2014 Chukong Technologies Inc.
 
http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
package zm.game.AClient;

import org.cocos2dx.lib.*;

public class AppActivity extends Cocos2dxActivity {
	//
	public Cocos2dxGLSurfaceView onCreateView() 
	{  
		Cocos2dxGLSurfaceView glSurfaceView = new Cocos2dxGLSurfaceView(this);  
      //glSurfaceView.setEGLConfigChooser(5, 6, 5, 0, 16, 8); 
        glSurfaceView.setEGLConfigChooser(8 , 8, 8, 8, 16, 8);
        return glSurfaceView;
	}
	
	static
	{
		//System.loadLibrary("mpg");
		//System.loadLibrary("mpg_v7a");
		//System.loadLibrary("openal");
	} 
	
	public static String getDeviceVendor(){
		return android.os.Build.MANUFACTURER;
    }
	public static String getDeviceModel(){
		return android.os.Build.BRAND+" "+android.os.Build.MODEL+" "+android.os.Build.PRODUCT;
    }
	
	@SuppressWarnings("deprecation")
	public static String getDeviceOS(){
		return "Android "+android.os.Build.VERSION.RELEASE+" sdk="+android.os.Build.VERSION.SDK;
    }
	
	public static String getCpuABI(){
		return android.os.Build.CPU_ABI+","+android.os.Build.CPU_ABI2;
    }
}
