#include "AnimatedSpriteInterface.h"

namespace Graphics
{
	AnimatedSpriteInterface::AnimatedSpriteInterface(bool clearExpired) : ClearExpired(clearExpired)
	{

	}
	void AnimatedSpriteInterface::Update(const sf::Uint32 time, const float TimeScale)
	{
		for (auto transform = ActiveTransforms.begin(); transform != ActiveTransforms.end(); ++transform)
		{
			transform->second->Update(time, TimeScale);
			if (ClearExpired && transform->second->GetExpired())
			{
				RemovalList.push_back(transform);
			}
		}
		if (ClearExpired && RemovalList.size() > 0)
		{
			for (auto it = RemovalList.begin(); it != RemovalList.end(); ++it)
			{
				ActiveTransforms.erase(*it);
			}
			RemovalList.clear();
		}
	}
	void AnimatedSpriteInterface::AddTransform(const std::string& index, boost::shared_ptr<BaseTransform> transform, bool overwriteExisting)
	{
		if (overwriteExisting)
		{
			ActiveTransforms[index] = transform;
		}
		else
		{
			auto it = ActiveTransforms.find(index);
			if (it == ActiveTransforms.end())
			{
				ActiveTransforms[index] = transform;
			}
		}
	}

	bool AnimatedSpriteInterface::RemoveTransform(const std::string index)
	{
		auto it = ActiveTransforms.find(index);
		if (it != ActiveTransforms.end())
		{
			ActiveTransforms.erase(it);
			return true;
		}
		return false;
	}

	void AnimatedSpriteInterface::ClearTransforms(const sf::Uint32 time, bool dispatchTranformFinishedEvents)
	{
		if (dispatchTranformFinishedEvents)
		{
			for (auto event = ActiveTransforms.begin(); event != ActiveTransforms.end(); ++event)
			{
				event->second->DispatchEvents(time);
			}
		}
		ActiveTransforms.clear();
	}

	bool AnimatedSpriteInterface::GetClearExpired()
	{
		return ClearExpired;
	}

	void AnimatedSpriteInterface::SetClearExpired(const bool value)
	{
		ClearExpired = value;
	}

	boost::unordered_map<std::string, boost::shared_ptr<BaseTransform> >& AnimatedSpriteInterface::GetActiveTransforms()
	{
		return ActiveTransforms;
	}
}