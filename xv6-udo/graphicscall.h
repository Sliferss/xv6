typedef enum {
    PIXEL,
    LINE,
    RECT,
    CIRCLE,
    TRIANGLE,
    PENTAGON,
    FILL_RECT,
    FILL_CIRCLE,
    FILL_PENTAGON,
    //enum to specificy draw type when in sysvideo
}drawtype;

struct drawParam {
    int param[4]; //coords and radius
    int colour;
    drawtype type;
};
//struct needed to be delcared in every file it's used so easier to make a header fille to be included