/*
 * OpenGLRenderForm.h
 *
 *  Created on: 18/gen/2011
 *      Author: Alkemist
 */

#ifndef OpenGLRenderForm_H_
#define OpenGLRenderForm_H_

#include <FApp.h>
#include <FBase.h>
#include <FSystem.h>
#include <FUi.h>
#include <FGraphicsOpengl.h>
#include <FGraphicsOpengl2.h>

#include "GL/GlCommons.h"

namespace DSBadaUtilityLib {

class OpenGLRenderForm: public Osp::Ui::Controls::Form,
        public Osp::Base::Runtime::Thread,
        public Osp::Base::Runtime::ITimerEventListener {

    public:
        OpenGLRenderForm();
        virtual ~OpenGLRenderForm();

    public:
        void OnTimerExpired(Osp::Base::Runtime::Timer & timer);
        virtual result OnInitializing(void);
        virtual result OnTerminating(void);

    private:

        void InitEGL();
        void DestroyEGL();

        Osp::Graphics::Opengl::EGLDisplay eDisplay;
        Osp::Graphics::Opengl::EGLSurface eSurface;
        Osp::Graphics::Opengl::EGLConfig eConfig;
        Osp::Graphics::Opengl::EGLContext eContext;

        Osp::Base::Runtime::Timer * _timer;
        bool isRendering;

    public:
        void StartRendering();
        void StopRendering();

    protected:
        virtual void OnStartRendering() = 0;
        virtual void OnStopRendering() = 0;
        virtual void OnDrawFrame() = 0;

    public:
        bool OnStart(void);
        void OnStop(void);

};

}

#endif /* OpenGLRenderForm_H_ */
