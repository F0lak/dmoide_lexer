#define UILIB_SLICE_WIDTH 32
#define UILIB_SLICE_HEIGHT 32

var/matrix/__uilib_translation_matrix = matrix()
var/matrix/__uilib_9slice_matrix = matrix()

#define matrix_translate(ref,x,y) __uilib_translation_matrix.c = x; __uilib_translation_matrix.f = y; ref.transform = __uilib_translation_matrix
#define matrix_9slice(ref,x,y,w,h) __uilib_9slice_matrix.c = x; __uilib_9slice_matrix.f = y; __uilib_9slice_matrix.a = w; __uilib_9slice_matrix.e = h; ref.transform = __uilib_9slice_matrix

proc
    resize_slicebox(list/slices, width=0, height=0, slice_width=UILIB_SLICE_WIDTH, slice_height=UILIB_SLICE_HEIGHT, x=0, y=0, start=1)
        var/stretch_x = (width / slice_width) - 2, stretch_y = (height / slice_height) - 2
        var/edge_x = x + width - slice_width, edge_y = y + height - slice_height
        var/center_x = x + (width - slice_width) / 2, center_y = y + (height - slice_height) / 2

        matrix_9slice(slices[start++],center_x,center_y,stretch_x,stretch_y)

        matrix_9slice(slices[start++],center_x,0,stretch_x,1)
        matrix_9slice(slices[start++],0,center_y,1,stretch_y)
        matrix_9slice(slices[start++],edge_x,center_y,1,stretch_y)
        matrix_9slice(slices[start++],center_x,edge_y,stretch_x,1)

        matrix_translate(slices[start++],x,y)
        matrix_translate(slices[start++],edge_x,y)
        matrix_translate(slices[start++],x,edge_y)
        matrix_translate(slices[start],edge_x,edge_y)