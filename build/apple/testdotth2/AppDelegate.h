//
//  AppDelegate.h
//  testdotth2
//
//  Created by jwkim on 2019/12/05.
//  Copyright © 2019 dotth. All rights reserved.
//

#import <Cocoa/Cocoa.h>

//@interface AppDelegate : NSObject <NSApplicationDelegate>
//
//
//@end


class  AppDelegate
{
public:
    AppDelegate()
    {
        
    }
    virtual ~AppDelegate()
    {
        
    }

    void initGLContextAttrs() {
        
    }
    int run(void) {
        while(true)
        {
            printf("asdf");
        }
        return 0;
    }
    
    /**
    @brief    Implement Director and Scene init code here.
    @return true    Initialize success, app continue.
    @return false   Initialize failed, app terminate.
    */
     bool applicationDidFinishLaunching()
    {
        return true;
    }

    /**
    @brief  Called when the application moves to the background
    @param  the pointer of the application
    */
     void applicationDidEnterBackground()
    {
        
    }

    /**
    @brief  Called when the application reenters the foreground
    @param  the pointer of the application
    */
     void applicationWillEnterForeground()
    {
        
    }
};
