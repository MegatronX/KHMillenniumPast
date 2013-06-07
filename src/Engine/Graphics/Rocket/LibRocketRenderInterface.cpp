#include "LibRocketRenderInterface.h"
#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <GL/GL.h>

#define GL_CLAMP_TO_EDGE 0x812F
namespace Graphics
{
	namespace RocketInterface
	{

		struct RocketSFMLRendererVertex
		{
			sf::Vector2f Position, TexCoord;
			sf::Color Color;
		};

		RocketSFMLRenderer::RocketSFMLRenderer(){
			//states = NULL;
			target = nullptr;//sf::RenderStates();
		}

		RocketSFMLRenderer::~RocketSFMLRenderer(){

		};


		// Called by Rocket when it wants to render geometry that it does not wish to optimise.
		void RocketSFMLRenderer::RenderGeometry(Rocket::Core::Vertex* vertices, int num_vertices, int* indices, int num_indices, const Rocket::Core::TextureHandle Image, const Rocket::Core::Vector2f& translation)
		{

			if(!target)return;

			target->setView(target->getDefaultView());

			target->pushGLStates();
			//glPushMatrix();

			sf::VertexArray v(sf::Triangles, num_indices);
			for(int j = 0; j < num_indices; j++){ //iterate indices
				int i = indices[j]; //i is the vertex position.
				v[j].position = sf::Vector2f(vertices[i].position.x, vertices[i].position.y);
				v[j].color = sf::Color(vertices[i].colour.red,vertices[i].colour.green,vertices[i].colour.blue, vertices[i].colour.alpha);
				if(Image){
					v[j].texCoords = sf::Vector2f(vertices[i].tex_coord.x*((sf::Texture*)Image)->getSize().x, vertices[i].tex_coord.y*((sf::Texture*)Image)->getSize().y);
				}
				//std::cout<<"tx: "<<v[j].TexCoords.x<<";"<<v[j].TexCoords.y<<std::endl;
			}
			states.blendMode = sf::BlendAlpha;
			states.texture = (sf::Texture*)Image;
			states.transform = sf::Transform::Identity;
			states.transform.translate(translation.x, translation.y);

			target->draw(v, states);
			//glPopMatrix();
			target->popGLStates();

		}

		// Called by Rocket when it wants to compile geometry it believes will be static for the forseeable future.		
		Rocket::Core::CompiledGeometryHandle RocketSFMLRenderer::CompileGeometry(Rocket::Core::Vertex* vertices, int num_vertices, int* indices, int num_indices, const Rocket::Core::TextureHandle Image)
		{

			//if(!GLEE_VERSION_2_0)			
			return (Rocket::Core::CompiledGeometryHandle)NULL;		

			/*
			vector<RocketOpenGLRendererVertex> Data;
			Data.resize(num_vertices);

			for(int i = 0; i < num_vertices; i++)
			{
			Data[i].Position = *(Vec2f*)&vertices[i].position;
			Data[i].TexCoord = *(Vec2f*)&vertices[i].tex_coord;
			Data[i].Color = Vec4f(float(vertices[i].colour.red) * 255, float(vertices[i].colour.green) * 255,
			float(vertices[i].colour.blue) * 255, float(vertices[i].colour.alpha) * 255);
			}

			RocketOpenGLRendererGeometryHandler *Geometry = new RocketOpenGLRendererGeometryHandler();
			Geometry->NumVertices = num_indices;

			glGenBuffers(1, &Geometry->VertexID);
			glBindBuffer(GL_ARRAY_BUFFER, Geometry->VertexID);
			glBufferData(GL_ARRAY_BUFFER, sizeof(RocketOpenGLRendererVertex) * num_vertices, &Data[0],
			GL_STATIC_DRAW);

			glGenBuffers(1, &Geometry->IndexID);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Geometry->IndexID);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * num_indices, indices, GL_STATIC_DRAW);

			glBindBuffer(GL_ARRAY_BUFFER, 0);

			Geometry->Image = Image;

			return (Rocket::Core::CompiledGeometryHandle)Geometry;*/
		};

		// Called by Rocket when it wants to render application-compiled geometry.		
		void RocketSFMLRenderer::RenderCompiledGeometry(Rocket::Core::CompiledGeometryHandle geometry, const Rocket::Core::Vector2f& translation)
		{
			/*RocketOpenGLRendererGeometryHandler *RealGeometry = (RocketOpenGLRendererGeometryHandler *)geometry;


			glPushMatrix();
			glTranslatef(translation.x, translation.y, 0);
			//glEnable(GL_BLEND);
			//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			sf::Texture *image = (sf::Texture*)RealGeometry->Image;

			if(image)
			{
			image->Bind();
			}
			else
			{
			glBindTexture(GL_TEXTURE_2D, 0);
			};

			glEnable(GL_VERTEX_ARRAY);
			glEnable(GL_TEXTURE_COORD_ARRAY);
			glEnable(GL_COLOR_ARRAY);

			#define BUFFER_OFFSET(x) ((char*)0 + x)

			glBindBuffer(GL_ARRAY_BUFFER, RealGeometry->VertexID);
			glVertexPointer(2, GL_FLOAT, sizeof(RocketOpenGLRendererVertex), BUFFER_OFFSET(0));
			glTexCoordPointer(2, GL_FLOAT, sizeof(RocketOpenGLRendererVertex), BUFFER_OFFSET(sizeof(Vec2f)));
			glColorPointer(4, GL_FLOAT, sizeof(RocketOpenGLRendererVertex), BUFFER_OFFSET(sizeof(Vec4f)));

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, RealGeometry->IndexID);
			glDrawElements(GL_TRIANGLES, RealGeometry->NumVertices, GL_UNSIGNED_INT, BUFFER_OFFSET(0));

			glBindBuffer(GL_ARRAY_BUFFER, 0);


			glDisable(GL_COLOR_ARRAY);
			glDisable(GL_TEXTURE_COORD_ARRAY);
			glDisable(GL_VERTEX_ARRAY);

			//glColor4f(1, 1, 1, 1);

			glPopMatrix();*/
		}

		// Called by Rocket when it wants to release application-compiled geometry.		
		void RocketSFMLRenderer::ReleaseCompiledGeometry(Rocket::Core::CompiledGeometryHandle geometry)
		{
			//delete (RocketOpenGLRendererGeometryHandler *)geometry;
		}

		// Called by Rocket when it wants to enable or disable scissoring to clip content.		
		void RocketSFMLRenderer::EnableScissorRegion(bool enable)
		{
			if (enable)
				glEnable(GL_SCISSOR_TEST);
			else
				glDisable(GL_SCISSOR_TEST);
		}

		// Called by Rocket when it wants to change the scissor region.
		void RocketSFMLRenderer::SetScissorRegion(int x, int y, int width, int height)
		{
			glScissor(x, target->getSize().y - (y + height), width, height);
			//glScissor(x, 768 - (y + height), width, height);
		}

		// Called by Rocket when a Image is required by the library.		
		bool RocketSFMLRenderer::LoadTexture(Rocket::Core::TextureHandle& texture_handle, Rocket::Core::Vector2i& texture_dimensions, const Rocket::Core::String& source)
		{
			/*sf::Texture *texture = new sf::Texture();

			if(!texture->loadFromFile(source.CString()))
			{
				delete texture;

				return false;
			};

			Image_handle = (Rocket::Core::TextureHandle) texture;
			Image_dimensions = Rocket::Core::Vector2i(texture->getSize().x, texture->getSize().y);

			return true;*/


			//TargetWindow->setActive();

			Rocket::Core::FileInterface* file_interface = Rocket::Core::GetFileInterface();
			Rocket::Core::FileHandle file_handle = file_interface->Open(source);
			if (file_handle == NULL)
				return false;

			file_interface->Seek(file_handle, 0, SEEK_END);
			size_t buffer_size = file_interface->Tell(file_handle);
			file_interface->Seek(file_handle, 0, SEEK_SET);

			char* buffer = new char[buffer_size];
			file_interface->Read(buffer, buffer_size, file_handle);
			file_interface->Close(file_handle);

			sf::Texture *texture = new sf::Texture();

			if(!texture->loadFromMemory(buffer, buffer_size))
			{
				delete buffer;
				delete texture;

				return false;
			};
			delete buffer;

			texture_handle = (Rocket::Core::TextureHandle) texture;
			auto size = texture->getSize();
			texture_dimensions = Rocket::Core::Vector2i(size.x, size.y);

			return true;
		}

		// Called by Rocket when a Image is required to be built from an internally-generated sequence of pixels.
		bool RocketSFMLRenderer::GenerateTexture(Rocket::Core::TextureHandle& texture_handle, const Rocket::Core::byte* source, const Rocket::Core::Vector2i& source_dimensions)
		{
			/*sf::Image *image = new sf::Image();
			sf::Texture *texture = new sf::Texture();

			image->create(source_dimensions.x, source_dimensions.y, source);

			texture->loadFromImage(*image);
			Image_handle = (Rocket::Core::TextureHandle)texture;

			return true;*/
			sf::Texture *texture = new sf::Texture();
			texture->create(source_dimensions.x, source_dimensions.y);
			texture->update(source, source_dimensions.x, source_dimensions.y, 0, 0);
			/*if(!texture->Update(source, source_dimensions.x, source_dimensions.y, 0, 0))
			{
				delete texture;

				return false;
			};*/

			texture_handle = (Rocket::Core::TextureHandle)texture;

			return true;
		}

		// Called by Rocket when a loaded Image is no longer required.		
		void RocketSFMLRenderer::ReleaseTexture(Rocket::Core::TextureHandle Image_handle)
		{
			delete (sf::Texture*)Image_handle;
		}
	}

}

