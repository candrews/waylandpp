/*
 * Copyright (c) 2014, Nils Christopher Brause
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer. 
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef WAYLAND_EGL_HPP
#define WAYLAND_EGL_HPP

#include <wayland-egl-core.h>
#include <EGL/egl.h>

namespace wayland
{
  class egl_window_t;
  class display_t;
  class surface_t;
}

// C++ Overrides for EGL functions that depend on native types

EGLDisplay eglGetDisplay(wayland::display_t &display);
EGLSurface eglCreateWindowSurface(EGLDisplay dpy, EGLConfig config,
				  wayland::egl_window_t &win,
				  const EGLint *attrib_list);

namespace wayland
{
  /** \brief Native EGL window
   */
  class egl_window_t
  {
  private:
    wl_egl_window *window;

    egl_window_t(const egl_window_t &);

    friend EGLSurface (::eglCreateWindowSurface)(EGLDisplay dpy, EGLConfig config,
                                               wayland::egl_window_t &win,
                                               const EGLint *attrib_list);

  public:
    /** \brief Create a native egl window for use with eglCreateWindowSurface
        \param surface The Wayland surface to use
        \param width Width of the EGL buffer
        \param height height of the EGL buffer
    */
    egl_window_t(surface_t &surface, int width, int height);
    ~egl_window_t();

    egl_window_t();
    egl_window_t(egl_window_t &&w);
    egl_window_t &operator=(egl_window_t &&w);

    void resize(int width, int height, int dx = 0, int dy = 0);
    void get_attached_size(int &width, int &height);
  };
}



#endif
