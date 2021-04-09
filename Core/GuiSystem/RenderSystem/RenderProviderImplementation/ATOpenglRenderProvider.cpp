#include "ATOpenglRenderProvider.hpp"
#include "../../../third_party_libs/gl3w/include/GL/gl3w.h"
#include "ATRenderProviderExceptions.hpp"
#include <sstream>

namespace at::core::gui::render
{
    auto OpenglRenderProvider::_get_shader_set_by_shader_type(SHADER_TYPE shader_type) -> std::set<uint_fast32_t>& {
        switch (shader_type)
        {
        case SHADER_TYPE::VERTEX: 
            return _vertex_shaders_id_collection;
        case SHADER_TYPE::FRAGMENT:
            return _fragment_shaders_id_collection;
        default:
            break;
        }
    }

    auto OpenglRenderProvider::_get_new_shader_by_shader_type(SHADER_TYPE shader_type) -> int {
        switch (shader_type)
        {
        case SHADER_TYPE::VERTEX: 
            return glCreateShader(GL_VERTEX_SHADER);
        case SHADER_TYPE::FRAGMENT:
            return glCreateShader(GL_FRAGMENT_SHADER);
        default:
            break;
        }
    }

    auto OpenglRenderProvider::_compile_shader_and_get_result(int shader_id, const char* buffer) -> std::pair<bool, u8string_at> {
        glShaderSource(shader_id, 1, &buffer, NULL);
        glCompileShader(shader_id);

        int success;
        char infoLog[512];
        glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);

        if (success)
            return {true, ""u8at};

        
        glGetShaderInfoLog(shader_id, 512, NULL, infoLog);
        return {false, "Shader compilation fail | shader_id: ["u8at + int_to_u8_at(shader_id) + "] \n"u8at + 
            u8string_at(buffer) + " | "u8at + infoLog};
    }

    auto OpenglRenderProvider::_add_shader(const char* shader_data, SHADER_TYPE shader_type) -> uint_fast32_t {
        int shader_id = _get_new_shader_by_shader_type(shader_type);
        auto compile_res = _compile_shader_and_get_result(shader_id, shader_data);
        if(!compile_res.first) {
            _logger->log_error(compile_res.second);
            throw exceptions::shader_compilation_error(compile_res.second);
        }

        std::set<uint_fast32_t> & shader_set = _get_shader_set_by_shader_type(shader_type);
        shader_set.insert(static_cast<uint_fast32_t>(shader_id));

        return shader_id;
    }

    OpenglRenderProvider::OpenglRenderProvider(std::shared_ptr<ILogger> logger, SDL_Window *window) : at_interface::IRenderProvider(logger, window) {
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
        SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 6);
        SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);

        _glcontext = SDL_GL_CreateContext(window);
        //_window = &window;

        select_render_context();
        
        if (gl3wInit()) {
            _logger->log_error("We cant init gl3w"u8at);
            throw exceptions::gl3w_error("We cant init gl3w"u8at);
        }

        if (!gl3wIsSupported(3, 3)){
            _logger->log_error("Opengl 3.3. not supported"u8at);
            throw exceptions::gl3w_error("Opengl 3.3. not supported"u8at);
        }
    }

    OpenglRenderProvider::~OpenglRenderProvider() {
        for(auto v_shader : _vertex_shaders_id_collection) {
            glDeleteShader(v_shader);
        }

        for(auto f_shader : _fragment_shaders_id_collection) {
            glDeleteShader(f_shader);
        }

        for(auto p_shader : _shader_programs_id_collection) {
            glDeleteProgram(p_shader);
        }
    }

    auto OpenglRenderProvider::draw_rectangle() -> void {
    }

    auto OpenglRenderProvider::draw_triangle() -> void {
    }

    auto OpenglRenderProvider::draw_circle() -> void {
    }

    auto OpenglRenderProvider::draw_text() -> void {
    }

    auto OpenglRenderProvider::draw_line() -> void {
    }

    auto OpenglRenderProvider::draw_frame() -> void {
    }

    auto OpenglRenderProvider::draw_image(std::shared_ptr<type::image::Image> image, uint_fast32_t shader_program_id, Rect<int_fast32_t> rect) -> void {
        /*float vertices[] = {
            // координаты (x,y,z)       // цвета            // текстурные координаты
            0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // верхняя правая
            0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // нижняя правая
            -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // нижняя левая
            -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // верхняя левая 
        };*/

        _logger->log_debug(U8StringBuilder{"w:[{8}] h:[{9}] r.x:[{10}] r.y:[{11}] r.w[{12}] r.h[{13}] [{0} | {1}] [{2} | {3}] [{4} | {5}] [{6} | {7}]"u8at}
            .fmt(0, static_cast<double_t>((rect.x + rect.width)-(_width/2))/(_width/2))
            .fmt(1, static_cast<double_t>((_height/2)-rect.y)/(_height/2))
            .fmt(2, static_cast<double_t>((rect.x + rect.width)-(_width/2))/(_width/2))
            .fmt(3, static_cast<double_t>((_height/2)-(rect.y + rect.height))/(_height/2))
            .fmt(4, static_cast<double_t>(rect.x-(_width/2))/(_width/2))
            .fmt(5, static_cast<double_t>((_height/2)-(rect.y + rect.height))/(_height/2))
            .fmt(6, static_cast<double_t>(rect.x-(_width/2))/(_width/2))
            .fmt(7, static_cast<double_t>((_height/2)-rect.y)/(_height/2))
            .fmt(8, _width)
            .fmt(9, _height)
            .fmt(10, rect.x)
            .fmt(11, rect.y)
            .fmt(12, rect.width)
            .fmt(13, rect.height));

        float vertices[] = {
            // координаты (x,y,z)                                                           // цвета            // текстурные координаты
            static_cast<double_t>((rect.x + rect.width)-(_width/2))/(_width/2),   static_cast<double_t>((_height/2)-rect.y)/(_height/2),                 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // правая верхняя
            static_cast<double_t>((rect.x + rect.width)-(_width/2))/(_width/2),   static_cast<double_t>((_height/2)-(rect.y + rect.height))/(_height/2), 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // правая нижняя
            static_cast<double_t>(rect.x-(_width/2))/(_width/2),                  static_cast<double_t>((_height/2)-(rect.y + rect.height))/(_height/2), 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // левая нижняя
            static_cast<double_t>(rect.x-(_width/2))/(_width/2),                  static_cast<double_t>((_height/2)-rect.y)/(_height/2),                 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // левая верхняя
        };

        unsigned int indices[] = {
            0, 1, 3, // первый треугольник
            1, 2, 3  // второй треугольник
        };

        unsigned int VBO, VAO, EBO;

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);

        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->get_width(), image->get_height(), 0, GL_RGB, GL_UNSIGNED_BYTE, image->get_data());
        glGenerateMipmap(GL_TEXTURE_2D);

        glBindTexture(GL_TEXTURE_2D, texture);    
        
        if(_shader_programs_id_collection.find(shader_program_id) == _shader_programs_id_collection.end())
            throw exceptions::shader_program_not_exist(shader_program_id);

        glUseProgram(shader_program_id);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }

    auto OpenglRenderProvider::add_shader(std::ifstream& shader_stream, SHADER_TYPE shader_type) -> uint_fast32_t{
        /*shader_stream.seekg(0, std::ios::end);
        std::streampos length = shader_stream.tellg();*/
        shader_stream.seekg(0, std::ios::beg);

        /*char* buffer = new char[static_cast<size_t>(length)];
        shader_stream.read(buffer, length);*/

        std::stringstream stream_buff{};
        stream_buff << shader_stream.rdbuf();

        _logger->log_debug(stream_buff.str());//u8string_at{buffer,static_cast<size_t>(length)});

        try {
            return _add_shader(stream_buff.str().c_str(), shader_type);//buffer, shader_type);
        } catch(std::exception ex) {
            //delete buffer;
            throw ex;
        }

        //delete buffer;
    }

    auto OpenglRenderProvider::add_shader(u8string_at shader_file_name, SHADER_TYPE shader_type) -> uint_fast32_t {
        std::ifstream file{shader_file_name};
        if(!file.is_open())
            throw std::runtime_error("File unavalable to open: ["u8at + shader_file_name + "]"u8at); 

        return add_shader(file, shader_type);
    }

    auto OpenglRenderProvider::add_shader(std::stringstream& shader_stream, SHADER_TYPE shader_type) -> uint_fast32_t {
        /*shader_stream.seekg(0, std::ios::end);
        size_t length = shader_stream.tellg();*/
        shader_stream.seekg(0, std::ios::beg);

        /*char* buffer = new char[length];
        shader_stream.read(buffer, length);*/

        try {
            return _add_shader(shader_stream.str().c_str(), shader_type);
        } catch(std::exception ex) {
            //delete buffer;
            throw ex;
        }

        //delete buffer;
    }

    auto OpenglRenderProvider::delete_shader(uint_fast32_t shader_id, SHADER_TYPE shader_type) -> void {
        std::set<uint_fast32_t> & shaders_id_set = _get_shader_set_by_shader_type(shader_type);

        auto id_ptr = shaders_id_set.find(shader_id);

        if(id_ptr == shaders_id_set.end())
            throw exceptions::shader_not_exist(static_cast<int>(shader_id), shader_type);

        glDeleteShader(static_cast<int>(*id_ptr));
        shaders_id_set.erase(id_ptr);
    }

    auto OpenglRenderProvider::add_shaders_program(std::map<SHADER_TYPE, uint_fast32_t> shaders_id_map) -> uint_fast32_t {
        int shader_program_id = glCreateProgram();

        for(auto shader_id : shaders_id_map) {
            auto shaders_id_set = _get_shader_set_by_shader_type(shader_id.first);
            if(shaders_id_set.find(shader_id.second) == shaders_id_set.end())
            {
                glDeleteProgram(shader_program_id);
                throw exceptions::shader_not_exist(static_cast<int>(shader_id.second), shader_id.first);
            }

            glAttachShader(shader_program_id, static_cast<int>(shader_id.second));
        }

        glLinkProgram(shader_program_id);

        int success;
        char infoLog[512];
        glGetProgramiv(shader_program_id, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shader_program_id, 512, NULL, infoLog);
            _logger->log_error(infoLog);
            throw exceptions::shader_program_link_error(infoLog);
        }

        _shader_programs_id_collection.insert(shader_program_id);
        return static_cast<uint_fast32_t>(shader_program_id);
    }

    auto OpenglRenderProvider::delete_shaders_program(uint_fast32_t shader_program_id) -> void {
        if(_shader_programs_id_collection.find(shader_program_id) == _shader_programs_id_collection.end())
            throw exceptions::shader_program_not_exist(shader_program_id);

        glDeleteProgram(static_cast<int>(shader_program_id));
    }

    auto OpenglRenderProvider::initialize_render_context(SDL_Window &window) -> void {
        
    }

    auto OpenglRenderProvider::select_render_context() -> void {
        SDL_GL_MakeCurrent(_window, _glcontext);
    }

    auto OpenglRenderProvider::prepare_new_frame(at::type::color::RGBA_at<uint8_t> color) -> void {
        glClearColor(color.r == 0 ? 0 : static_cast<float_t>(color.r)/255, 
        color.g == 0 ? 0 : static_cast<float_t>(color.g)/255,
        color.b == 0 ? 0 : static_cast<float_t>(color.b)/255,
        color.a == 0 ? 0 : static_cast<float_t>(color.a)/255);

        glClear(GL_COLOR_BUFFER_BIT);

        SDL_GetWindowSize(_window, &_width, &_height);
    }
}