#include    <vsg/all.h>

int main(int argc, char *argv[])
{
    vsg::ref_ptr<vsg::WindowTraits> traits = vsg::WindowTraits::create();
    traits->windowTitle = "Hello, Vulkan Scene Graph!";
    traits->width = 1280;
    traits->height = 720;
    traits->fullscreen = false;

    vsg::ref_ptr<vsg::Group> scene = vsg::Group::create();

    vsg::ref_ptr<vsg::Viewer> viewer = vsg::Viewer::create();

    vsg::ref_ptr<vsg::Window> window(vsg::Window::create(traits));

    viewer->addWindow(window);

    vsg::ref_ptr<vsg::Perspective> perspective;

    perspective = vsg::Perspective::create(30.0,
                                           static_cast<double>(window->extent2D().width) / static_cast<double>(window->extent2D().height),
                                           0.0001,
                                           10000.0);

    //vsg::ref_ptr<vsg::Camera> camera = vsg::Camera(perspective)

    viewer->compile();

    while(viewer->advanceToNextFrame())
    {
        viewer->handleEvents();

        viewer->update();

        viewer->recordAndSubmit();

        viewer->present();
    }

    return 0;
}
