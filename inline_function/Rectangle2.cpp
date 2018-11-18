// Accessors & mutators with "get" and "set"
class Rectangle {
        int width, height;
        public:
        Rectangle(int w = 0, int h = 0)
                : width(w), height(h) {}
        int getWidth() const { return width; }
        void setWidth(int w) { width = w; }
        int getHeight() const { return height; }
        void setHeight(int h) { height = h; }
};

int main() {
        Rectangle r(19, 47);
        // Change width & height:

        // mutator = set, accessor = get  
        r.setHeight(2 * r.getWidth());
        r.setWidth(2 * r.getHeight());
} ///:~
