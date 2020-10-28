#include <iostream>

struct box_t
{
    size_t position;
    size_t volume;
};

int main()
{
    size_t n = 0;
    std::cin >> n;

    box_t *boxes = new box_t[n];

    for (size_t i = 0; i < n; i++)
    {
        size_t a = 0, b = 0, c = 0;
        std::cin >> a >> b >> c;
        boxes[i].position = i;
        boxes[i].volume = a + b + c;
    }

    box_t tmp;

    for (size_t i = 1; i < n; ++i)
    {
        tmp.position = boxes[i].position;
        tmp.volume = boxes[i].volume;

        size_t j = i;

        for (; j > 0 && tmp.volume < boxes[j - 1].volume; --j)
        {
            boxes[j].position = boxes[j - 1].position;
            boxes[j].volume = boxes[j - 1].volume;
        }
        boxes[j].position = tmp.position;
        boxes[j].volume = tmp.volume;
    }

    for (size_t i = 0; i < n; ++i)
        std::cout << boxes[i].position << " ";

    std::cout << std::endl;

    delete[] boxes;
}
