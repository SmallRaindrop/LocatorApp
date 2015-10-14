#import <UIKit/UIKit.h>
#import "client/ios/BreakpadController.h"

int main(int argc, char *argv[]) {
    [[BreakpadController sharedInstance]start: YES];
    [[BreakpadController sharedInstance] setUploadingEnabled:YES];
    
    NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
    int retVal = UIApplicationMain(argc, argv, nil, @"AppController");
    [pool release];

    [[BreakpadController sharedInstance]stop];
    
    return retVal;
}

