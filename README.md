#LMBasicDraw: [Leap Motion](https://www.leapmotion.com) basic drawing APP#
This APP is a basic drawing APP wich uses the [Leap Motion Controller](https://www.leapmotion.com)


##Windows:##
###Dependencies###
1. Visual Studio 2012
2. [Leap Motion SDK](https://developer.leapmotion.com/downloads) (a developer account is needed)
3. [Cinder C++ Library](http://libcinder.org/download/)

###Build###
1. Create source directory e.g.: `C:\LM_Apps`
2. Download the [Leap Motion SDK](https://developer.leapmotion.com/downloads)
3. Extract the `LeapDeveloperKit_release_win_<VERSION>.zip` into the source directory
4. Download the [Cinder C++ Library](http://libcinder.org/download/)
5. Extract the `cinder_<VERSION>_vc2012.zip` into the source directory and rename the `cinder_<VERSION>_vc2012` directory to `Cinder`
6. Open the solution `./vc11/LMBasicDraw.sln` in Visual Studio 2012
7. Build and run
8. Output can be found in `./vc11/dist`


##OSX:##
###Dependencies###
1. Xcode 5
2. [Leap Motion SDK](https://developer.leapmotion.com/downloads) (a developer account is needed)
3. [Cinder C++ Library](http://libcinder.org/download/)

###Build###
1. Create source directory e.g.: `~/LM_Apps`
2. Download the [Leap Motion SDK](https://developer.leapmotion.com/downloads)
3. Copy the contents of the `LeapDeveloperKit_release_mac_<VERSION>.dmg` into the source directory
4. Download the [Cinder C++ Library](http://libcinder.org/download/)
5. Extract the `cinder_<VERSION>_mac.zip` into the source directory and rename the `cinder_<VERSION>_mac` directory to `Cinder`
6. Open the solution `./xcode/LMBasicDraw.xcodeproj` in Xcode
7. Build and run


##Help:##
* To draw use only on finger of one hand
* Move this finger forward to the controller untils the cursor circle turn green
* Move this finger above the controller to draw strokes
* Press 'f' key to toggle fullscreen
* Press 'x' key to clear drawing
* Press 'ESC' to quit the APP

