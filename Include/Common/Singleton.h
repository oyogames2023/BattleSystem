#pragma once

#include "Commom.h"

namespace zeus
{

	template <typename T>
	class Singleton
	{
	public:

		static T& GetInstance()
		{
			std::call_once(instanceFlag_, [&] {
				instance_ = new T();
				instance_->Initialize();
				std::atexit(DestoryInstance);
			});
			return *instance_;
		}

	protected:

		Singleton() = default;

		virtual ~Singleton() = default;

	private:

		static void DestoryInstance()
		{
			if (nullptr != instance_)
			{
				instance_->Destory();
				delete instance_;
				instance_ = nullptr;
			}
		}

	private:

		static T* instance_;

		static std::once_flag instanceFlag_;
	};

	template <typename T>
	T* Singleton<T>::instance_ = nullptr;

	template <typename T>
	std::once_flag Singleton<T>::instanceFlag_;

} // namespace zeus