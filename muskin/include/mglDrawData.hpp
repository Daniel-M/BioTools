#ifndef MATHGL_H
    #include<mgl2/mgl.h>
    #define MATHGL_H
#endif

int mglDrawData( std::string sFile, point_t ptRangeA, point_t ptRangeB)
{
	std::string Title("Mesh generated from " + sFile + "\n see " + sFile +".xml for details");
	std::string out_datafile(sFile + "-mgl.png");

	// Be careful, this extension must be changed, this line if for test only
	sFile+=".msh";

	mglGraph plot;
	mglData points(sFile.c_str());

	plot.SetSize(1200,900);          ///gr->SetSize(1200,900) Set image size in pixels
	plot.SetMarkSize(0.7);    /// gr->SetMarkSize(0.0005) Set size of the marker, i.e. the dot size on plot
	
	plot.Alpha(true); plot.Light(true); //plot.Transparent(false);
	
	plot.Title(Title.c_str(),"iC",8);
    
	plot.SetFontSize(4);  /// gr->SetFontSize(4) Sets the global font size for the plot ticks and related

//	plot.Rotate(50,60);

	plot.Box();
		
	//plot.Mesh(points);
	//plot.Plot(points);
	plot.SetRanges(ptRangeA[0],ptRangeB[0],ptRangeA[1],ptRangeB[1]);
	plot.Axis();
	plot.Plot(points.SubData(0),points.SubData(1),"r #o"); 

	plot.WritePNG(out_datafile.c_str(),"",false); ///gr->WritePNG(out_datafile.c_str(),"",false) put the plot on a PNG file
	

	////mglData a(50,40);
	//mglGraph gr;
	////a.Modify("0.6*sin(2*pi*x)*sin(3*pi*y) + 0.4*cos(3*pi*(x*y))");

	////gr.Rotate(40,60);
	//gr.Box();
	//gr.SetRanges(-1,6,-1,11);
	//gr.Axis();

    //gr.Rotate(50,60);
	////gr.Mesh(points.SubData(0),points.SubData(1)); 
	//gr.Mesh(points);
	//gr.WritePNG("example.png","",false); ///gr->WritePNG(out_datafile.c_str(),"",false) put the plot on a PNG file

	return 0;
}
