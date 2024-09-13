#include "Application.h"

namespace zeus
{

	ApplicationBase::ApplicationBase()
	{

	}

	ApplicationBase::~ApplicationBase()
	{

	}

	bool ApplicationBase::LoadConfig()
	{
		return true;
	}

	uint64_t ApplicationBase::GetCurrentMilliseconds() const
	{
		return dt_.GetCurrentMilliseconds();
	}

	uint64_t ApplicationBase::GetCurrentSeconds() const
	{
		return dt_.GetCurrentSeconds();
	}

	uint32_t ApplicationBase::GetYear() const
	{
		return dt_.GetYear();
	}

	uint32_t ApplicationBase::GetMonth() const
	{
		return dt_.GetMonth();
	}

	uint32_t ApplicationBase::GetDay() const
	{
		return dt_.GetDay();
	}

	uint32_t ApplicationBase::GetHour() const
	{
		return dt_.GetHour();
	}

	uint32_t ApplicationBase::GetMinute() const
	{
		return dt_.GetMinute();
	}

	uint32_t ApplicationBase::GetSecond() const
	{
		return dt_.GetSecond();
	}

	Application::Application()
	{

	}

	Application::~Application()
	{

	}

} // namespace zeus