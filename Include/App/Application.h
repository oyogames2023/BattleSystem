#pragma once

#include "Commom.h"
#include "Singleton.h"
#include "DateTime.h"

namespace zeus
{

	class ApplicationBase
	{
	public:

		ApplicationBase();

		virtual ~ApplicationBase();

	public:

		bool LoadConfig();

	public:

		uint64_t GetCurrentMilliseconds() const;

		uint64_t GetCurrentSeconds() const;

		uint32_t GetYear() const;

		uint32_t GetMonth() const;

		uint32_t GetDay() const;

		uint32_t GetHour() const;

		uint32_t GetMinute() const;

		uint32_t GetSecond() const;

	private:

		std::string serviceName_;

		DateTime dt_;
	};

	class Application
		: public ApplicationBase
		, public Singleton<Application>
	{
	public:

		Application();

		~Application();
	};

} // namespace zeus