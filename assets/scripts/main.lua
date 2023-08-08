local pixels = {};

local ii = 0;
function randomColor()
    ii = ii + 1;
    if ii == 1 then
        return 0XFF0000FF;
    elseif ii == 2 then
        return 0XFFFF00FF;
    elseif ii == 3 then
        ii = 0;
        return 0XFF00FFFF;
    end
    -- local r = math.random(0, 255);
    -- local g = math.random(0, 255);
    -- local b = math.random(0, 255);

    -- return r << 24 | g << 16 | b << 8 | 255;
end

local width = 64;
local height = 32;

for i = 0, width do
    for j = 0, height do
        pixels[i * (height+1) + j] = randomColor()
    end
end

image(pixels, width, height);