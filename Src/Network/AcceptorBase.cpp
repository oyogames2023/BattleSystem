﻿#include "AcceptorBase.h"
#include "EventLoop.h"

namespace zeus::network
{

	AcceptorBase::AcceptorBase(EventLoopPtr loop, const std::string& ip, int32_t port)
		: loop_(loop)
		, ip_(ip)
		, port_(port)
	{
		uv_tcp_init(loop_->GetUVLoop().get(), &server_);
		struct sockaddr_in addr;
		uv_ip4_addr(ip.c_str(), port, &addr);
		uv_tcp_bind(&server_, (const struct sockaddr*)&addr, 0);
		server_.data = this;
	}

	std::string AcceptorBase::GetListenAddress() const
	{
		return ip_;
	}

	int32_t AcceptorBase::GetListenPort() const
	{
		return port_;
	}

} // namespace zeus::network
