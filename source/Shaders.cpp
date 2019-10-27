#include "Shaders.h"
std::string vertexShader="", fragmentShader="", geometryShader="";

void updateTheCode(std::string code)
{

vertexShader =std::string()+
"#version 330\n"+

"in vec2 pos;"+

"void main()"+
"{"+
"   gl_Position = vec4(pos.x,pos.y,0,1);"+
"}";


fragmentShader =std::string()+
"#version 330\n"+

"in vec4 fColor;"+
"out vec4 fragColor;"+

"void main()"+
"{"+
"   fragColor = fColor;"+
"}";

geometryShader = std::string()+
"#version 330\n"+

"layout (lines) in;"+
"layout (line_strip, max_vertices=100) out;"+

"out vec4 fColor;"+

"uniform float scale;"+
"uniform mat4 ortho;"+
"uniform float supply;"+

"vec2 multiply(vec2 a, vec2 b)"+
"{"+
"  return vec2(a.x*b.x - a.y*b.y, a.x*b.y + a.y*b.x);"+
"}"+

"vec2 divide(vec2 a, vec2 b)"+
"{"+
" float mb = b.x*b.x + b.y*b.y;"+
" return vec2( (a.x*b.x + a.y*b.y)/mb , (a.y*b.x - a.x*b.y)/mb );  "+
"}"+

"void main()"+
"{"+
"   float newscale = 2*scale + 1;"+
"   float delta = 1/newscale;"+
"   fColor = vec4(0,0.7f,1,1);"+

"   for(float i=0; i<=1; i=i+delta)"+
"   {"+
"       vec2 z = (1-i)*gl_in[0].gl_Position.xy + i*gl_in[1].gl_Position.xy;"+
"       vec2 start = z;"+
"       vec2 end = "+code+";"+
"       vec2 diff = end - start;"+
"       vec2 interpolate = start + diff*supply;"+

"       gl_Position =ortho*vec4(interpolate,0,1);"+

"       if(gl_in[0].gl_Position.x == 0 && gl_in[1].gl_Position.x == 0)"+
"           fColor = vec4(0.5f,1,0,1);"+
"       if(gl_in[0].gl_Position.y == 0 && gl_in[1].gl_Position.y == 0)"+
"           fColor = vec4(0.5f,1,0,1);"+

"       EmitVertex();"+
"   }"+

"   EndPrimitive();"+

"}";

}
