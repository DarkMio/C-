#include <vector>
#include "Surface.h"
#include "Canvas.h"

#pragma once

namespace GUI {

    enum LayoutFlags {
        topleft = 0,
        botright = 1,
        spaced = 1 << 1,
        distributed = 1 << 2    
    };

    /**
     * To be fair: There is no way to remove elements right now.
     */
    class ILayoutManager {
        public:
        virtual void add(Canvas const& element, LayoutFlags const& flags) = 0;
        virtual bool draw(Surface const& surface, Rectangle const& rect) = 0;
		// virtual ~ILayoutManager() {};
	};

    class FreeLayout : ILayoutManager {
        private:
        std::vector<Canvas> canvas_elements;
        public:
        FreeLayout();
        void add(Canvas const& element, LayoutFlags const& flags) override;
        bool draw(Surface const& surface, Rectangle const& rect) override;
		~FreeLayout() override {};
	};

    class HorizontalLayout : ILayoutManager {
        private:
        std::vector<Canvas> canvas_elements;
        public:
        HorizontalLayout();
        void add(Canvas const& element, LayoutFlags const& flags) override;
        bool draw(Surface const& surface, Rectangle const& rect) override;
		~HorizontalLayout() override {};
	};
/*
    class VerticalLayout : ILayoutManager {
        private:
        std::vector<Canvas> canvas_elements;
        public:
        void add(Canvas const& element, LayoutFlags const& flags);
        void setLayout(Rectangle const& rect, LayoutFlags const& flags);
        void draw(Surface const& surface, Rectangle const& rect);
    }
*/
}