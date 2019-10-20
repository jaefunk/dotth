/*
Licensed under the MIT License <http://opensource.org/licenses/MIT>.
Copyright (c) 2019 jaefunk <https://github.com/jaefunk/dotth>.

Permission is hereby  granted, free of charge, to any  person obtaining a copy
of this software and associated  documentation files (the "Software"), to deal
in the Software  without restriction, including without  limitation the rights
to  use, copy,  modify, merge,  publish, distribute,  sublicense, and/or  sell
copies  of  the Software,  and  to  permit persons  to  whom  the Software  is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE  IS PROVIDED "AS  IS", WITHOUT WARRANTY  OF ANY KIND,  EXPRESS OR
IMPLIED,  INCLUDING BUT  NOT  LIMITED TO  THE  WARRANTIES OF  MERCHANTABILITY,
FITNESS FOR  A PARTICULAR PURPOSE AND  NONINFRINGEMENT. IN NO EVENT  SHALL THE
AUTHORS  OR COPYRIGHT  HOLDERS  BE  LIABLE FOR  ANY  CLAIM,  DAMAGES OR  OTHER
LIABILITY, WHETHER IN AN ACTION OF  CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE  OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef __DOTTH_RENDERER_HPP__
#define __DOTTH_RENDERER_HPP__

#include <vector>

#include "base/utility.hpp"

namespace dotth {
	namespace gl_callback {
        void timer(int value);
        void display(void);
        void reshape(int width, int height);
	};
    
    class render_command {
    public:
        enum class command_type
        {
            unknown,    // Reserved type.*/
            triangles,  // Triangles command, used to draw triangles.*/
//            QUAD,       // Quad command, used for draw quad.*/
//            CUSTOM,     // Custom command, used for calling callback for rendering.*/
//            BATCH,      // Batch command, used for draw batches in texture atlas.*/
//            GROUP,      // Group command, which can group command in a tree hierarchy.*/
//            MESH,       // Mesh command, used to draw 3D meshes.*/
//            PRIMITIVE,  // Primitive command, used to draw primitives such as lines, points and triangles.*/
        };
        
    public:
        const command_type type(void) { return _type; }
        const float depth(void) { return _depth; }
        
    protected:
        command_type _type = command_type::unknown;
        float _depth = 0.f;
        bool _ortho = false;
    };
    
    class renderer : public utility::singleton<renderer> {
    public:
        void init_gl(int argc, char** argv);
        
        std::vector<render_command> a;
    };
};

#endif // __DOTTH_RENDERER_HPP__
