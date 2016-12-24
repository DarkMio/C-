#pragma once

#include "LayoutManager.h"

namespace GUI {

	class HorizontalLayout : public LayoutManager {
		private:
		std::vector<std::shared_ptr<LayoutManager>> m_children;
		public:
		virtual std::tuple<int, int> preferredSize() const override;
		virtual std::tuple<int, int> minimumSize() const override;
		virtual bool draw(Surface const& surface, Rectangle const& rect) const override;
		virtual void add(std::shared_ptr<LayoutManager> layout, Uint32 const& lflags) override;
		virtual ~HorizontalLayout();
	};

	class VerticalLayout : public LayoutManager {
		private:
		std::vector<std::shared_ptr<LayoutManager>> m_children;
		public:
		virtual std::tuple<int, int> preferredSize() const override;
		virtual std::tuple<int, int> minimumSize() const override;
		virtual bool draw(Surface const& surface, Rectangle const& rect) const override;
		virtual void add(std::shared_ptr<LayoutManager> layout, Uint32 const& lflags) override;
		virtual ~VerticalLayout();
	};

	class HorizontalCloseLayout : public HorizontalLayout {
		private:
		std::vector<std::shared_ptr<LayoutManager>> m_children;
		public:
		virtual std::tuple<int, int> preferredSize() const override;
		virtual std::tuple<int, int> minimumSize() const override;
		virtual bool draw(Surface const& surface, Rectangle const& rect) const override;
		virtual void add(std::shared_ptr<LayoutManager> layout, Uint32 const& lflags) override;
		virtual ~HorizontalCloseLayout();
	};

	class PixelSpace : public LayoutManager {
		private:
		Surface m_surface;
		std::tuple<int, int> m_minSize;
		mutable bool m_dirty;
		public:
		virtual std::tuple<int, int> preferredSize() const override;
		virtual std::tuple<int, int> minimumSize() const override;
		PixelSpace() = delete;
		PixelSpace(int const& width, int const& height, Uint32 const& fill);
		virtual bool draw(Surface const& surface, Rectangle const& rect) const override;
		virtual void add(std::shared_ptr<LayoutManager> layout, Uint32 const& lflags) override;
		virtual ~PixelSpace();
	};
}