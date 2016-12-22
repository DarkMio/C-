#include "LayoutManager.h"

namespace GUI {

    FreeLayout::FreeLayout() : canvas_elements() {
    }

    void FreeLayout::add(Canvas const& element, LayoutFlags const& flags) {
        canvas_elements.push_back(element);
        // Flags are omitted
    }

    bool FreeLayout::draw(Surface const& surface, Rectangle const& rect) {
        bool hasDrawn = false;
        for(Canvas c: canvas_elements) {
            hasDrawn |= c.draw(surface, rect);
        }
        return hasDrawn;
    }

    HorizontalLayout::HorizontalLayout() : canvas_elements() {
    }

    void HorizontalLayout::add(Canvas const& element, LayoutFlags const& flags) {
        canvas_elements.push_back(element);
        // Flags are omitted
    }

    bool HorizontalLayout::draw(Surface const& surface, Rectangle const& rect) {
        auto count = canvas_elements.size();
        int distributed_space = rect.w / count;
        int current = 0;
        bool hasDrawn = false;
        for(Canvas c: canvas_elements) {
            Rectangle drawSpace(distributed_space, rect.h, current * distributed_space, rect.y);
            hasDrawn |= c.draw(surface, drawSpace);
        }
        return hasDrawn;
    }
}