#include <tuple>
#include <functional>


#pragma once
class IDrawable {
	public:
		virtual std::tuple<int, int> size() = 0;
		virtual void update() = 0;
		virtual void setUpdateHandler(std::function<void()> const&) = 0;
		virtual ~IDrawable() {};
};
