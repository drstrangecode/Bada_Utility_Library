/*
 * OpenGLRenderForm.cpp
 *
 *  Created on: 18/gen/2011
 *  Author: Alkemist
 */

#include "Forms/OpenGLRenderForm.h"
#include "GL/GlCommons.h"
#include "GL/Util3D.h"

using namespace Osp::App;
using namespace Osp::Base;
using namespace Osp::Base::Runtime;
using namespace Osp::Ui;
using namespace Osp::Ui::Controls;
using namespace Osp::System;
using namespace Osp::Graphics::Opengl;

namespace DSBadaUtilityLib {

#define TIMER_INTERVAL_MS 10

OpenGLRenderForm::OpenGLRenderForm() {
	isRendering = false;
}

OpenGLRenderForm::~OpenGLRenderForm() {
}

bool OpenGLRenderForm::OnStart() {
    AppLog("OpenGLRenderForm::OnStart() [Starting render thread]");

    InitEGL();

    OnStartRendering();

    _timer = new Timer();
    _timer->Construct(*this);
    _timer->Start(TIMER_INTERVAL_MS);

    return true;
}

void OpenGLRenderForm::OnStop() {
    AppLog("OpenGLRenderForm::OnStop() [Stopping render thread]");

    _timer->Cancel();
    delete _timer;

    DestroyEGL();

    OnStopRendering();

}

result OpenGLRenderForm::OnInitializing(void) {
    result r = E_SUCCESS;
    return r;
}

result OpenGLRenderForm::OnTerminating(void) {
    result r = E_SUCCESS;
    StopRendering();
    return r;
}

void OpenGLRenderForm::StartRendering() {
    AppLog("OpenGLRenderForm::StartRendering()");

    if (isRendering) return;

    isRendering = true;

    Thread::Construct(THREAD_TYPE_EVENT_DRIVEN);
    this->Start();

}

void OpenGLRenderForm::StopRendering() {
	AppLog("OpenGLRenderForm::StopRendering()");

	if (!isRendering) return;

	isRendering = false;

    this->Stop();
    this->Join();
}

void OpenGLRenderForm::InitEGL() {
    AppLog("OpenGLRenderForm::InitEGL()");

    eglBindAPI(EGL_OPENGL_ES_API);
    AppAssertf(EGL_SUCCESS == eglGetError(), "eglBindAPI failed");

    EGLint numConfigs = 1;

    EGLint eConfigList[] = {
            EGL_RED_SIZE, 5, // Comment disables code formatter
            EGL_GREEN_SIZE, 6, // Comment disables code formatter
            EGL_BLUE_SIZE, 5, // Comment disables code formatter
            EGL_ALPHA_SIZE, 0, // Comment disables code formatter
            EGL_DEPTH_SIZE, 8, // Comment disables code formatter
            EGL_RENDERABLE_TYPE, EGL_OPENGL_ES_BIT, // Comment disables code formatter
            EGL_SURFACE_TYPE, EGL_WINDOW_BIT, // Comment disables code formatter
            EGL_NONE // Comment disables code formatter
            };

    eDisplay = eglGetDisplay((EGLNativeDisplayType) EGL_DEFAULT_DISPLAY);
    AppAssertf(EGL_SUCCESS == eglGetError(), "eDisplay failed");

    eglInitialize(eDisplay, NULL, NULL);
    AppAssertf(EGL_SUCCESS == eglGetError(), "eglInitialize failed");

    eglChooseConfig(eDisplay, eConfigList, &eConfig, 1, &numConfigs);
    AppAssertf(EGL_SUCCESS == eglGetError(), "eglChooseConfig failed");

    eSurface = eglCreateWindowSurface(eDisplay, eConfig, (EGLNativeWindowType) this, null);
    AppAssertf(EGL_NO_SURFACE != eSurface && EGL_SUCCESS == eglGetError(), "eglCreateWindowSurface failed");

    eContext = eglCreateContext(eDisplay, eConfig, EGL_NO_CONTEXT, null);
    AppAssertf(EGL_SUCCESS == eglGetError(), "eglCreateContext failed");

    eglMakeCurrent(eDisplay, eSurface, eSurface, eContext);
    AppAssertf(EGL_SUCCESS == eglGetError(), "eglMakeCurrent failed");

}

void OpenGLRenderForm::DestroyEGL() {
    if (eDisplay) {
        eglMakeCurrent(eDisplay, null, null, null);

        if (eContext) {
            eglDestroyContext(eDisplay, eContext);
            eContext = EGL_NO_CONTEXT;
        }

        if (eSurface) {
            eglDestroySurface(eDisplay, eSurface);
            eSurface = EGL_NO_SURFACE;
        }

        eglTerminate(eDisplay);
        eDisplay = EGL_NO_DISPLAY;
    }
}

void OpenGLRenderForm::OnTimerExpired(Osp::Base::Runtime::Timer & timer) {
	_timer->Start(TIMER_INTERVAL_MS);

    OnDrawFrame();
    eglSwapBuffers(eDisplay, eSurface);
}

}
