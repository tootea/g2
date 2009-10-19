##############################################################################
##  Copyright (C) 2007  Dr. Tijs Michels
##  This file is part of the g2 library

##  Note that these are just my personal preferences

### user-specified dimensions (can be changed)

total_width = 815.0
total_height = 565.0
fr_margin = 5.0
step_c = 18
x_inner_margin = 28
scale_marker_length = 6
x_axis_text_width = 46
y_axis_text_width = 62
font_size = 28
x_font_size = font_size
y_font_size = font_size
x_axis_text_height = x_font_size
max_x_val = 12 # for twelve months
x11_scale_factor = 1.25

### no changes below this point

### compiler-defined dimensions (based on the above)

x_width = int(x11_scale_factor * total_width)
x_height = int(x11_scale_factor * total_height)

fr_right = total_width - fr_margin
fr_top = total_height - fr_margin

fr_w = fr_right - fr_margin
fr_h = fr_top - fr_margin
fr_h_i = fr_h * x_inner_margin
fr_pr = fr_h / fr_w
y_inner_margin = fr_h_i / fr_w

min_x = fr_margin + x_inner_margin
min_y = fr_margin + y_inner_margin
max_x = fr_right - x_inner_margin
max_y = fr_top - y_inner_margin

min_gr_x = min_x + y_axis_text_width
min_gr_y = min_y + x_axis_text_height
max_gr_w = max_x - min_gr_x
max_gr_h = max_y - min_gr_y

x_scale_marker_length = scale_marker_length * fr_pr
max_x_val_d = max_x_val + max_x_val
step_x = max_gr_w / max_x_val
st_h_x = max_gr_w / max_x_val_d
