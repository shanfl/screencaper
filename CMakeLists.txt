
project(rop)

set(src 
ScreenCapture.cpp
RopWindow.h
AlphaChild.h
stdafx.h)

set(res resource.h screenCapture.rc)

add_executable(screenCapture WIN32 ${src} ${res})
