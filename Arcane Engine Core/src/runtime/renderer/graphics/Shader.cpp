#include "pch.h"
#include "Shader.h"

namespace arcane {

	Shader::Shader(const std::string &path) : m_ShaderFilePath(path) {
		std::string shaderBinary = FileUtils::readFile(m_ShaderFilePath);
		auto shaderSources = preProcessShaderBinary(shaderBinary);
		compile(shaderSources);
	}

	Shader::~Shader() {
		glDeleteProgram(m_ShaderID);
	}

	unsigned int Shader::load() {
		// Create the program
		unsigned int program = glCreateProgram();
		int result;

		// Vertex Shader
		unsigned int vertex = glCreateShader(GL_VERTEX_SHADER);
		std::string vertSourceString = editor::FileUtils::readFile(m_VertPath);
		const char *vertSource = vertSourceString.c_str();

		glShaderSource(vertex, 1, &vertSource, NULL);
		glCompileShader(vertex);

		// Check to see if it was successful
		glGetShaderiv(vertex, GL_COMPILE_STATUS, &result);
		if (result == GL_FALSE || vertSourceString.empty()) {
			int length;
			glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &length);
			if (length > 0) {
				std::vector<char> error(length);
				glGetShaderInfoLog(vertex, length, &length, &error[0]);
				std::string errorString(error.begin(), error.end());

				ARCANE_ERROR(m_VertPath + errorString);
			}
			else {
				ARCANE_ERROR(m_VertPath + std::string("unknown error"));
			}
			glDeleteShader(vertex);
			return 0;
		}

		//Fragment Shader
		unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);
		std::string fragSourceString = editor::FileUtils::readFile(m_FragPath);
		const char *fragSource = fragSourceString.c_str();

		glShaderSource(fragment, 1, &fragSource, NULL);
		glCompileShader(fragment);

		// Check to see if it was successful
		glGetShaderiv(fragment, GL_COMPILE_STATUS, &result);
		if (result == GL_FALSE || fragSourceString.empty()) {
			int length;
			glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &length);
			if (length > 0) {
				std::vector<char> error(length);
				glGetShaderInfoLog(fragment, length, &length, &error[0]);
				std::string errorString(error.begin(), error.end());

				ARCANE_ERROR(m_FragPath + errorString);
			}
			else {
				ARCANE_ERROR(m_FragPath + std::string("error unknown"));
			}
			glDeleteShader(fragment);
			return 0;
		}

		// Geometry shader (optional)
		unsigned int geometry;
		if (m_GeomPath != "") {
			geometry = glCreateShader(GL_GEOMETRY_SHADER);
			std::string geomSourceString = editor::FileUtils::readFile(m_GeomPath);
			const char *geomSource = geomSourceString.c_str();

			glShaderSource(geometry, 1, &geomSource, NULL);
			glCompileShader(geometry);

			// Check to see if it was successful
			glGetShaderiv(geometry, GL_COMPILE_STATUS, &result);
			if (result == GL_FALSE || geomSourceString.empty()) {
				int length;
				glGetShaderiv(geometry, GL_INFO_LOG_LENGTH, &length);
				if (length > 0) {
					std::vector<char> error(length);
					glGetShaderInfoLog(geometry, length, &length, &error[0]);
					std::string errorString(error.begin(), error.end());

					ARCANE_ERROR(m_GeomPath + errorString);
				}
				else {
					ARCANE_ERROR(m_GeomPath + std::string("error unknown"));
				}
				glDeleteShader(geometry);
				return 0;
			}
		}

		// Hull Shader (optional)
		unsigned int hull;
		if (m_HullShader != "") {
			hull = glCreateShader(GL_TESS_CONTROL_SHADER);
			std::string hullSourceString = editor::FileUtils::readFile(m_HullShader);
			const char *hullSource = hullSourceString.c_str();

			glShaderSource(hull, 1, &hullSource, NULL);
			glCompileShader(hull);

			glGetShaderiv(hull, GL_COMPILE_STATUS, &result);
			if (result == GL_FALSE || hullSourceString.empty()) {
				int length;
				glGetShaderiv(hull, GL_INFO_LOG_LENGTH, &length);
				if (length > 0) {
					std::vector<char> error(length);
					glGetShaderInfoLog(hull, length, &length, &error[0]);
					std::string errorString(error.begin(), error.end());

					ARCANE_ERROR(m_HullShader + errorString);
				}
				else {
					ARCANE_ERROR(m_HullShader + std::string("error unknown"));
				}
				glDeleteShader(hull);
				return 0;
			}
		}

		// Domain Shader (optional)
		unsigned int domain;
		if (m_DomainShader != "") {
			domain = glCreateShader(GL_TESS_EVALUATION_SHADER);
			std::string domainSourceString = editor::FileUtils::readFile(m_DomainShader);
			const char *domainSource = domainSourceString.c_str();

			glShaderSource(domain, 1, &domainSource, NULL);
			glCompileShader(domain);

			glGetShaderiv(domain, GL_COMPILE_STATUS, &result);
			if (result == GL_FALSE || domainSourceString.empty()) {
				int length;
				glGetShaderiv(domain, GL_INFO_LOG_LENGTH, &length);
				if (length > 0) {
					std::vector<char> error(length);
					glGetShaderInfoLog(domain, length, &length, &error[0]);
					std::string errorString(error.begin(), error.end());

					ARCANE_ERROR(m_DomainShader + errorString);
				}
				else {
					ARCANE_ERROR(m_DomainShader + std::string("error unknown"));
				}
				glDeleteShader(domain);
				return 0;
			}
		}

		// Attach the shaders to the program and link them
		glAttachShader(program, vertex);
		glAttachShader(program, fragment);
		if (m_GeomPath != "")
			glAttachShader(program, geometry);
		if (m_HullShader != "")
			glAttachShader(program, hull);
		if (m_DomainShader != "")
			glAttachShader(program, domain);

		glLinkProgram(program);
		glValidateProgram(program);

		// Delete the vertex and fragment shaders
		glDeleteShader(vertex);
		glDeleteShader(fragment);
		if (m_GeomPath != "")
			glDeleteShader(geometry);
		if (m_HullShader != "")
			glDeleteShader(hull);
		if (m_DomainShader != "")
			glDeleteShader(domain);

		// Return the program id
		return program;
	void Shader::enable() const {
		glUseProgram(m_ShaderID);
	}

	void Shader::disable() const {
		glUseProgram(0);
	}

	void Shader::setUniform(const char* name, float value) {
		glUniform1f(getUniformLocation(name), value);
	}

	void Shader::setUniform(const char* name, int value) {
		glUniform1i(getUniformLocation(name), value);
	}

	void Shader::setUniform(const char* name, const glm::vec2& vector) {
		glUniform2f(getUniformLocation(name), vector.x, vector.y);
	}

	void Shader::setUniform(const char *name, const glm::ivec2& vector) {
		glUniform2i(getUniformLocation(name), vector.x, vector.y);
	}

	void Shader::setUniform(const char* name, const glm::vec3& vector) {
		glUniform3f(getUniformLocation(name), vector.x, vector.y, vector.z);
	}

	void Shader::setUniform(const char *name, const glm::ivec3& vector) {
		glUniform3i(getUniformLocation(name), vector.x, vector.y, vector.z);
	}

	void Shader::setUniform(const char* name, const glm::vec4& vector) {
		glUniform4f(getUniformLocation(name), vector.x, vector.y, vector.z, vector.w);
	}

	void Shader::setUniform(const char* name, const glm::ivec4& vector) {
		glUniform4i(getUniformLocation(name), vector.x, vector.y, vector.z, vector.w);
	}

	void Shader::setUniform(const char* name, const glm::mat3& matrix) {
		glUniformMatrix3fv(glGetUniformLocation(m_ShaderID, name), 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void Shader::setUniform(const char* name, const glm::mat4& matrix) {
		glUniformMatrix4fv(glGetUniformLocation(m_ShaderID, name), 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void Shader::setUniformArray(const char *name, int arraySize, float *value) {
		glUniform1fv(glGetUniformLocation(m_ShaderID, name), arraySize, value);
	}

	void Shader::setUniformArray(const char *name, int arraySize, int *value) {
		glUniform1iv(glGetUniformLocation(m_ShaderID, name), arraySize, value);
	}

	void Shader::setUniformArray(const char *name, int arraySize, glm::vec2 *value) {
		glUniform2fv(glGetUniformLocation(m_ShaderID, name), arraySize, glm::value_ptr(*value));
	}

	void Shader::setUniformArray(const char *name, int arraySize, glm::ivec2 *value) {
		glUniform2iv(glGetUniformLocation(m_ShaderID, name), arraySize, glm::value_ptr(*value));
	}

	void Shader::setUniformArray(const char *name, int arraySize, glm::vec3 *value) {
		glUniform3fv(glGetUniformLocation(m_ShaderID, name), arraySize, glm::value_ptr(*value));
	}

	void Shader::setUniformArray(const char *name, int arraySize, glm::ivec3 *value) {
		glUniform3iv(glGetUniformLocation(m_ShaderID, name), arraySize, glm::value_ptr(*value));
	}

	void Shader::setUniformArray(const char *name, int arraySize, glm::vec4 *value) {
		glUniform4fv(glGetUniformLocation(m_ShaderID, name), arraySize, glm::value_ptr(*value));
	}

	void Shader::setUniformArray(const char *name, int arraySize, glm::ivec4 *value) {
		glUniform4iv(glGetUniformLocation(m_ShaderID, name), arraySize, glm::value_ptr(*value));
	}

	int Shader::getUniformLocation(const char* name) {
		return glGetUniformLocation(m_ShaderID, name);
	}

	GLenum Shader::shaderTypeFromString(const std::string &type) {
		if (type == "vertex") {
			return GL_VERTEX_SHADER;
		}
		else if (type == "fragment") {
			return GL_FRAGMENT_SHADER;
		}
		else if (type == "geometry") {
			return GL_GEOMETRY_SHADER;
		}
		else if (type == "hull") {
			return GL_TESS_CONTROL_SHADER;
		}
		else if (type == "domain") {
			return GL_TESS_EVALUATION_SHADER;
		}
		else if (type == "compute") {
			return GL_COMPUTE_SHADER;
		}

		// TODO: Should assert false here, unknown shader type: 'type'
		return 0;
	}

	std::unordered_map<GLenum, std::string> Shader::preProcessShaderBinary(std::string &source) {
		std::unordered_map<GLenum, std::string> shaderSources;

		const char *shaderTypeToken = "#shader-type";
		size_t shaderTypeTokenLength = strlen(shaderTypeToken);
		size_t pos = source.find(shaderTypeToken);
		while (pos != std::string::npos) {
			size_t eol = source.find_first_of("\r\n", pos);
			// TODO: eol == std::string::npos, if so then we have a syntax error
			size_t begin = pos + shaderTypeTokenLength + 1;
			std::string shaderType = source.substr(begin, eol - begin);
			// TODO: type != "vertex" || fragment || hull || domain || compute, if so then we have an invalid shader type specified

			size_t nextLinePos = source.find_first_not_of("\r\n", eol);
			pos = source.find(shaderTypeToken, nextLinePos);
			shaderSources[shaderTypeFromString(shaderType)] = source.substr(nextLinePos, pos - (nextLinePos == std::string::npos ? source.size() - 1 : nextLinePos));
		}

		return shaderSources;
	}

	void Shader::compile(const std::unordered_map<GLenum, std::string> &shaderSources) {
		m_ShaderID = glCreateProgram();

		// Attach different components of the shader (vertex, fragment, geometry, hull, domain, or compute)
		for (auto &item : shaderSources) {
			GLenum type = item.first;
			const std::string &source = item.second;

			GLuint shader = glCreateShader(type);
			const GLchar *shaderSource = source.c_str();
			glShaderSource(shader, 1, &shaderSource, NULL);
			glCompileShader(shader);

			// Check to see if compiling was successful
			GLint wasCompiled;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &wasCompiled);
			if (wasCompiled == GL_FALSE || source.empty()) {
				int length;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);

				if (length > 0) {
					std::vector<char> error(length);
					glGetShaderInfoLog(shader, length, &length, &error[0]);
					std::string errorString(error.begin(), error.end());

					Logger::getInstance().error("logged_files/shader_compile_error.txt", m_ShaderFilePath, errorString);
				}
				else {
					Logger::getInstance().error("logged_files/shader_compile_error.txt", m_ShaderFilePath, "unknown error");
				}
				glDeleteShader(shader);
				break;
			}

			glAttachShader(m_ShaderID, shader);
			glDeleteShader(shader);
		}

		// Validate shader
		glLinkProgram(m_ShaderID);
		glValidateProgram(m_ShaderID);
	}

}