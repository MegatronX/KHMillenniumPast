#include <graphics/DrawManager.h>

namespace Graphics
{
	DrawManager::DrawManager()
	{

	}

	void DrawManager::Draw(sf::RenderWindow &window)
	{
		for (auto layer = Drawables.begin(); layer != Drawables.end(); ++layer)
		{
			for (auto drawable = layer->second.first.begin(); drawable != layer->second.first.end(); ++drawable)
			{
				if (!drawable->second.ShaderSet)
				{
					drawable->second.DrawEntry->Draw(window);
				}
				else
				{
					drawable->second.DrawEntry->Draw(window, drawable->second.AttachedShader);
				}
			}
			for (auto drawable = layer->second.second.begin(); drawable != layer->second.second.end(); ++drawable)
			{
				if (!drawable->second.ShaderSet)
				{
					drawable->second.DrawEntry->Draw(window);
				}
				else
				{
					drawable->second.DrawEntry->Draw(window, drawable->second.AttachedShader);
				}
			}
		}
	}

	void DrawManager::Draw(sf::RenderWindow &window, sf::Shader &shader)
	{
		for (auto layer = Drawables.begin(); layer != Drawables.end(); ++layer)
		{
			for (auto drawable = layer->second.first.begin(); drawable != layer->second.first.end(); ++drawable)
			{
				if (!drawable->second.ShaderSet)
				{
					drawable->second.DrawEntry->Draw(window, shader);
				}
				else
				{
					drawable->second.DrawEntry->Draw(window, drawable->second.AttachedShader);
				}
			}
			for (auto drawable = layer->second.second.begin(); drawable != layer->second.second.end(); ++drawable)
			{
				if (!drawable->second.ShaderSet)
				{
					drawable->second.DrawEntry->Draw(window, shader);
				}
				else
				{
					drawable->second.DrawEntry->Draw(window, drawable->second.AttachedShader);
				}
			}
		}
	}

	void DrawManager::Update(const sf::Uint32 time, const float TimeScale)
	{
		for (auto layer = Drawables.begin(); layer != Drawables.end(); ++layer)
		{
			for (auto drawable = layer->second.second.begin(); drawable != layer->second.second.end(); ++drawable)
			{
				drawable->second.DrawEntry->Update(time, TimeScale);
			}
		}
	}

	void DrawManager::Update(const float time, const float TimeScale)
	{
		for (auto layer = Drawables.begin(); layer != Drawables.end(); ++layer)
		{
			for (auto drawable = layer->second.second.begin(); drawable != layer->second.second.end(); ++drawable)
			{
				drawable->second.DrawEntry->Update(time, TimeScale);
			}
		}
	}

	void DrawManager::AddDrawable(const std::string& index, boost::shared_ptr<DrawInterface> drwIntr, int layer)
	{
		Drawables[layer].first[index] = DrawableEntry<DrawInterface>(drwIntr);
	}

	void DrawManager::AddAnimatedDrawable(const std::string& index, boost::shared_ptr<AnimatedDraw> animDrw, const int layer)
	{
		Drawables[layer].second[index] = DrawableEntry<AnimatedDraw>(animDrw);
	}

	bool DrawManager::RemoveDrawable(const int layer, const std::string& index)
	{
		bool rem = false;
		auto finder = Drawables[layer].first.find(index);
		if (finder != Drawables[layer].first.end())
		{
			Drawables[layer].first.erase(finder);
		}
		return rem;
	}
	bool DrawManager::RemoveAnimatedDrawable(const int layer, const std::string& index)
	{
		bool rem = false;
		auto finder = Drawables[layer].second.find(index);
		if (finder != Drawables[layer].second.end())
		{
			Drawables[layer].second.erase(finder);
			rem = true;
		}
		return rem;
	}
	bool DrawManager::RemoveAnyDrawable(const std::string& index)
	{
		bool rem = false;
		for (auto layer = Drawables.begin(); layer != Drawables.end(); ++layer)
		{
			auto l1 = layer->second.first.find(index);
			if (l1 != layer->second.first.end())
			{
				layer->second.first.erase(l1);
				rem = true;
			}

			auto l2 = layer->second.second.find(index);
			if (l2 != layer->second.second.end())
			{
				layer->second.second.erase(l2);
				rem = true;
			}
		}
		return rem;
	}

	bool DrawManager::LoadShader(const std::string& shaderFile, const std::string& index, const int layer, const sf::Shader::Type stype)
	{
		bool set = false;
		auto finder = Drawables[layer].first.find(index);
		if (finder != Drawables[layer].first.end())
		{
			set = finder->second.AttachedShader.loadFromFile(shaderFile, stype);
		}
		return set;
	}

	/*void DrawManager::SetShader(const sf::Shader& shader, const std::string& index, const int layer)
	{
		auto finder = Drawables[layer].first.find(index);
		if (finder != Drawables[layer].first.end())
		{
			//finder->second.AttachedShader. = shader;
		}
	}*/

	bool DrawManager::LoadAnimatedShader(const std::string& shaderFile, const std::string& index, const int layer, const sf::Shader::Type stype)
	{
		bool set = false;
		auto finder = Drawables[layer].second.find(index);
		if (finder != Drawables[layer].second.end())
		{
			set = finder->second.AttachedShader.loadFromFile(shaderFile, stype);
		}
		return set;
	}

	/*void DrawManager::SetAnimatedShader(const sf::Shader& shader, const std::string& index, const int layer)
	{
		auto finder = Drawables[layer].second.find(index);
		if (finder != Drawables[layer].second.end())
		{
			//finder->second.AttachedShader = shader;
		}
	}*/
}