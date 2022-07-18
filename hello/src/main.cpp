#include    <vsg/all.h>
#include    <vsgXchange/all.h>

int main(int argc, char *argv[])
{
    (void) argc;
    (void) argv;

    vsg::ref_ptr<vsg::WindowTraits> traits = vsg::WindowTraits::create();
    traits->windowTitle = "Hello, Vulkan Scene Graph!";
    traits->width = 1280;
    traits->height = 720;
    traits->fullscreen = false;

    vsg::ref_ptr<vsg::Group> scene = vsg::Group::create();

    vsg::ref_ptr<vsg::Options> options = vsg::Options::create();
    options->add(vsgXchange::all::create());
    vsg::Path filepath(L"../data/cessna.vsgt");
    auto root = vsg::read_cast<vsg::Node>(filepath, options);
    scene->addChild(root);

    vsg::ref_ptr<vsg::Viewer> viewer = vsg::Viewer::create();

    vsg::ref_ptr<vsg::Window> window(vsg::Window::create(traits));

    viewer->addWindow(window);

    vsg::ref_ptr<vsg::Perspective> perspective;

    double aspect = static_cast<double>(window->extent2D().width) /
            static_cast<double>(window->extent2D().height);

    perspective = vsg::Perspective::create(
                30.0,
                aspect,
                0.0001,
                10000.0);


    vsg::ref_ptr<vsg::LookAt> LookAt = vsg::LookAt::create();

    vsg::ref_ptr<vsg::Camera> camera = vsg::Camera::create(
                perspective,
                LookAt,
                vsg::ViewportState::create(window->extent2D()));

    viewer->addEventHandler(vsg::Trackball::create(camera));

    vsg::ref_ptr<vsg::CommandGraph> commandGraph =
            vsg::createCommandGraphForView(window, camera, scene);

    viewer->assignRecordAndSubmitTaskAndPresentation({commandGraph});

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
