// Component: CMake.Documentation.SphinxHTML

function Component()
{
    // Default constructor
}

Component.prototype.createOperations = function()
{
    // Create shortcut
    if (installer.value("os") === "win") {

        component.addOperation("CreateShortcut",
                               installer.value("TargetDir") + "/doc/cmake-3.5/html/index.html",
                               installer.value("StartMenuDir") + "/CMake Documentation.lnk");

    }

    // Call default implementation
    component.createOperations();
}
