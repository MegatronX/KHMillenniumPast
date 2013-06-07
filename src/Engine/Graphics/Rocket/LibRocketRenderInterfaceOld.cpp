#include "LibRocketRenderInteraceOld.h"
#include <Rocket/Core.h>
#include <sfml/OpenGL.hpp>
#include <GL/GL.h>

#define GL_CLAMP_TO_EDGE 0x812F
namespace Graphics
{
	namespace RocketInterface
	{
		void SetupOpenGL2DView(const sf::View& view, const float AdditionalXTrans = 0.0f, float AdditionalYTrans = 0.0f)
		{
			sf::Vector2f size = view.getSize();
			sf::Vector2f center = view.getCenter();
			sf::Vector2f position = center - size / 2.f;

			// Edit the OpenGL projection matrix
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();

			// Setup translation (according to left-upper corner) and scale
			glOrtho(0., size.x, size.y, 0., -1., 1.);
			glTranslatef(-position.x + AdditionalXTrans, -position.y + AdditionalYTrans, 0.f);

			// Setup rotation 
			glTranslatef(center.x, center.y, 0.f);
			glRotatef(view.getRotation(), 0.f, 0.f, -1.f);
			glTranslatef(-center.x, -center.y, 0.f);
		}
#ifdef ENABLE_GLEE
#include <GL/glee.h>

		class RocketSFMLRendererGeometryHandler
		{
		public:
			GLuint VertexID, IndexID;
			int NumVertices;
			Rocket::Core::TextureHandle Texture;

			RocketSFMLRendererGeometryHandler() : VertexID(0), IndexID(0), Texture(0), NumVertices(0)
			{
			};

			~RocketSFMLRendererGeometryHandler()
			{
				if(VertexID)
					glDeleteBuffers(1, &VertexID);

				if(IndexID)
					glDeleteBuffers(1, &IndexID);

				VertexID = IndexID = 0;
			};
		};

#endif

		struct RocketSFMLRendererVertex
		{
			sf::Vector2f Position, TexCoord;
			sf::Color Color;
		};

		RocketSFMLRenderer::RocketSFMLRenderer()
		{
		}

		void RocketSFMLRenderer::SetWindow(sf::RenderWindow *Window)
		{
			TargetWindow = Window;

			Resize();
		};

		sf::RenderWindow *RocketSFMLRenderer::GetWindow()
		{
			return TargetWindow;
		};

		void RocketSFMLRenderer::Resize()
		{
			TargetWindow->setActive(true);
			//TargetWindow->SaveGLStates();

			static sf::View View;
			auto size = TargetWindow->getSize();
			View.setSize(size.x, size.y);
			View.setCenter(TargetWindow->getView().getCenter());
			//View.SetSize(sf::FloatRect(0, (float)TargetWindow->GetWidth(), (float)TargetWindow->GetHeight(), 0));
			TargetWindow->setView(View);

			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			glOrtho(0, size.x, size.y, 0, -1, 1);
			//glOrtho(0, TargetWindow->getSize().x, TargetWindow->getSize().y, 0, -1, 1);
			glMatrixMode(GL_MODELVIEW);

			glViewport(0, 0, size.x, size.y);
			//glViewport(0, 0, TargetWindow->getSize().x, TargetWindow->getSize().y);
		};

		/*void RocketSFMLRenderer::RenderGeometry(Rocket::Core::Vertex* vertices, int num_vertices, int* indices, int num_indices, const Rocket::Core::TextureHandle texture, const Rocket::Core::Vector2f& translation)
		{
			TargetWindow->SaveGLStates();
			TargetWindow->SetActive();

			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glEnable(GL_BLEND);

			// Store attributes and assign them
			glPushAttrib(GL_DEPTH_BITS | GL_TEXTURE_BIT);
			glDisable(GL_DEPTH_TEST);
			glEnable(GL_TEXTURE_2D);

			// Bind texture - instead of glBindTexture(GL_TEXTURE_2D, id)
			//mTexture->Bind();
			//glTranslatef(translation.x, translation.y, 0);
			// Initialize projection matrix (2D view)
			glMatrixMode(GL_PROJECTION);
			glPushMatrix();
			SetupOpenGL2DView(TargetWindow->GetView(), translation.x, translation.y);

			// Initialize modelview matrix
			glMatrixMode(GL_MODELVIEW);
			glPushMatrix();




			std::vector<Rocket::Core::Vector2f> Positions(num_vertices);
			std::vector<Rocket::Core::Colourb> Colors(num_vertices);
			std::vector<Rocket::Core::Vector2f> TexCoords(num_vertices);

			for(int  i = 0; i < num_vertices; i++)
			{
				Positions[i] = vertices[i].position;
				Colors[i] = vertices[i].colour;
				TexCoords[i] = vertices[i].tex_coord;
			};

			glEnableClientState(GL_VERTEX_ARRAY);
			glEnableClientState(GL_COLOR_ARRAY);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);

			glVertexPointer(2, GL_FLOAT, 0, &Positions[0]);
			glColorPointer(4, GL_UNSIGNED_BYTE, 0, &Colors[0]);
			glTexCoordPointer(2, GL_FLOAT, 0, &TexCoords[0]);

			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			sf::Texture *sftexture = (sf::Texture *)texture;

			if(sftexture)
			{
				sftexture->Bind();
			}
			else
			{
				glDisableClientState(GL_TEXTURE_COORD_ARRAY);
				glBindTexture(GL_TEXTURE_2D, 0);
			};

			glDrawElements(GL_TRIANGLES, num_indices, GL_UNSIGNED_INT, indices);

			glDisableClientState(GL_VERTEX_ARRAY);
			glDisableClientState(GL_COLOR_ARRAY);
			glDisableClientState(GL_TEXTURE_COORD_ARRAY);

			glColor4f(1, 1, 1, 1);





			//Restoration based on Thor Particles

			// Restore projection matrix
			glMatrixMode(GL_PROJECTION);
			glPopMatrix();

			// Restore modelview matrix
			glMatrixMode(GL_MODELVIEW); 
			glPopMatrix();

			// Restore attributes
			glPopAttrib();

			// Switch back, restore SFML's OpenGL state
			TargetWindow->RestoreGLStates();

		}*/

		void RocketSFMLRenderer::RenderGeometry(Rocket::Core::Vertex* vertices, int num_vertices, int* indices, int num_indices, const Rocket::Core::TextureHandle texture, const Rocket::Core::Vector2f& translation)
		{

			//glPushMatrix();
			glTranslatef(translation.x, translation.y, 0);

			std::vector<Rocket::Core::Vector2f> Positions(num_vertices);
			std::vector<Rocket::Core::Colourb> Colors(num_vertices);
			std::vector<Rocket::Core::Vector2f> TexCoords(num_vertices);

			for(int  i = 0; i < num_vertices; i++)
			{
				Positions[i] = vertices[i].position;
				Colors[i] = vertices[i].colour;
				TexCoords[i] = vertices[i].tex_coord;
			};

			glEnableClientState(GL_VERTEX_ARRAY);
			glEnableClientState(GL_COLOR_ARRAY);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);

			glVertexPointer(2, GL_FLOAT, 0, &Positions[0]);
			glColorPointer(4, GL_UNSIGNED_BYTE, 0, &Colors[0]);
			glTexCoordPointer(2, GL_FLOAT, 0, &TexCoords[0]);

			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			sf::Texture *image = (sf::Texture *)texture;

			if(image)
			{
				image->bind();
			}
			else
			{
				glDisableClientState(GL_TEXTURE_COORD_ARRAY);
				glBindTexture(GL_TEXTURE_2D, 0);
			};

			glDrawElements(GL_TRIANGLES, num_indices, GL_UNSIGNED_INT, indices);

			glDisableClientState(GL_VERTEX_ARRAY);
			glDisableClientState(GL_COLOR_ARRAY);
			glDisableClientState(GL_TEXTURE_COORD_ARRAY);

			glColor4f(1, 1, 1, 1);

			//glPopMatrix();
		}
		
		Rocket::Core::CompiledGeometryHandle RocketSFMLRenderer::CompileGeometry(Rocket::Core::Vertex* vertices,
			int num_vertices, int* indices,
			int num_indices,
			const Rocket::Core::TextureHandle texture)
		{
#ifdef ENABLE_GLEE
			TargetWindow->setActive();

			if(!GLEE_VERSION_2_0)
				return (Rocket::Core::CompiledGeometryHandle) NULL;

			std::vector<RocketSFMLRendererVertex> Data(num_vertices);

			for(unsigned long i = 0; i < Data.size(); i++)
			{
				Data[i].Position = *(sf::Vector2f*)&vertices[i].position;
				Data[i].TexCoord = *(sf::Vector2f*)&vertices[i].tex_coord;
				Data[i].Color = sf::Color(vertices[i].colour.red, vertices[i].colour.green,
					vertices[i].colour.blue, vertices[i].colour.alpha);
			};

			RocketSFMLRendererGeometryHandler *Geometry = new RocketSFMLRendererGeometryHandler();
			Geometry->NumVertices = num_indices;

			glGenBuffers(1, &Geometry->VertexID);
			glBindBuffer(GL_ARRAY_BUFFER, Geometry->VertexID);
			glBufferData(GL_ARRAY_BUFFER, sizeof(RocketSFMLRendererVertex) * num_vertices, &Data[0],
				GL_STATIC_DRAW);

			glGenBuffers(1, &Geometry->IndexID);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Geometry->IndexID);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * num_indices, indices, GL_STATIC_DRAW);

			glBindBuffer(GL_ARRAY_BUFFER, 0);

			Geometry->Texture = texture;

			return (Rocket::Core::CompiledGeometryHandle)Geometry;
#else
			return NULL;
#endif
		}

		void RocketSFMLRenderer::RenderCompiledGeometry(Rocket::Core::CompiledGeometryHandle geometry, const Rocket::Core::Vector2f& translation)
		{
#ifdef ENABLE_GLEE
			TargetWindow->setActive();

			RocketSFMLRendererGeometryHandler *RealGeometry = (RocketSFMLRendererGeometryHandler *)geometry;

			glPushMatrix();
			glTranslatef(translation.x, translation.y, 0);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			sf::Image *image = (sf::Image *)RealGeometry->texture;

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
			glVertexPointer(2, GL_FLOAT, sizeof(RocketSFMLRendererVertex), BUFFER_OFFSET(0));
			glTexCoordPointer(2, GL_FLOAT, sizeof(RocketSFMLRendererVertex), BUFFER_OFFSET(sizeof(sf::Vector2f)));
			glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(RocketSFMLRendererVertex), BUFFER_OFFSET(sizeof(sf::Vector2f[2])));

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, RealGeometry->IndexID);
			glDrawElements(GL_TRIANGLES, RealGeometry->NumVertices, GL_UNSIGNED_INT, BUFFER_OFFSET(0));

			glBindBuffer(GL_ARRAY_BUFFER, 0);

			glDisable(GL_COLOR_ARRAY);
			glDisable(GL_TEXTURE_COORD_ARRAY);
			glDisable(GL_VERTEX_ARRAY);

			glColor4f(1, 1, 1, 1);

			glPopMatrix();
#else
			//ROCKET_ASSERT(false & Rocket::Core::String("Not Implemented"));
#endif
		}

		void RocketSFMLRenderer::ReleaseCompiledGeometry(Rocket::Core::CompiledGeometryHandle geometry)
		{
#ifdef ENABLE_GLEE
			TargetWindow->setActive();

			delete (RocketSFMLRendererGeometryHandler *)geometry;
#else
			//ROCKET_ASSERT(false & Rocket::Core::String("Not Implemented"));
#endif
		}

		void RocketSFMLRenderer::EnableScissorRegion(bool enable)
		{
			TargetWindow->setActive();

			if (enable)
				glEnable(GL_SCISSOR_TEST);
			else
				glDisable(GL_SCISSOR_TEST);
		}
		void RocketSFMLRenderer::SetScissorRegion(int x, int y, int width, int height)
		{
			TargetWindow->setActive();

			glScissor(x, TargetWindow->getSize().y - (y + height), width, height);
		}
		bool RocketSFMLRenderer::LoadTexture(Rocket::Core::TextureHandle& texture_handle, Rocket::Core::Vector2i& texture_dimensions, const Rocket::Core::String& source)
		{
			TargetWindow->setActive();

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
			texture_dimensions = Rocket::Core::Vector2i(texture->getSize().x, texture->getSize().y);

			return true;
		}
		bool RocketSFMLRenderer::GenerateTexture(Rocket::Core::TextureHandle& texture_handle, const Rocket::Core::byte* source, const Rocket::Core::Vector2i& source_dimensions)
		{
			TargetWindow->setActive();

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

		void RocketSFMLRenderer::ReleaseTexture(Rocket::Core::TextureHandle texture_handle)
		{
			TargetWindow->setActive();

			delete (sf::Texture *)texture_handle;
		}
	}
}
