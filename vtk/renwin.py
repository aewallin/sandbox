from vtk import*
 
# Sphere
sphereSource =vtkSphereSource();
sphereSource.SetCenter(-4.0, 0.0, 0.0);
sphereSource.SetRadius(4.0);
 
sphereMapper =vtkPolyDataMapper();
sphereMapper.SetInputConnection(sphereSource.GetOutputPort());
 
sphereActor =vtkActor();
sphereActor.SetMapper(sphereMapper);
 
# Regular Polygon
regularPolygonSource =vtkRegularPolygonSource();
regularPolygonSource.SetCenter(4.0, 0.0, 0.0);
regularPolygonSource.SetRadius(4.0);
 
regularPolygonMapper =vtkPolyDataMapper();
regularPolygonMapper.SetInputConnection(regularPolygonSource.GetOutputPort());
 
regularPolygonActor =vtkActor();
regularPolygonActor.SetMapper(regularPolygonMapper);
 
# A renderer and render window
renderer =vtkRenderer();
renderWindow =vtkRenderWindow();
renderWindow.AddRenderer(renderer);
 
# An interactor
renderWindowInteractor =vtkRenderWindowInteractor();
renderWindowInteractor.SetRenderWindow(renderWindow);
 
# Create the widget
balloonRep =vtkBalloonRepresentation();
balloonRep.SetBalloonLayoutToImageRight();
 
balloonWidget =vtkBalloonWidget();
balloonWidget.SetInteractor(renderWindowInteractor);
balloonWidget.SetRepresentation(balloonRep);
balloonWidget.AddBalloon(sphereActor,"This is a sphere");
balloonWidget.AddBalloon(regularPolygonActor,"This is a regular polygon");
 
# Add the actors to the scene
renderer.AddActor(sphereActor);
renderer.AddActor(regularPolygonActor);
 
# Render an image (lights and cameras are created automatically)
renderWindow.Render();
balloonWidget.EnabledOn();
 
# Begin mouse interaction
renderWindowInteractor.Start();
