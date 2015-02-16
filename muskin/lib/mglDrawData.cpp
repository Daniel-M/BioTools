#include "headers.hpp"

int mglDrawData( std::string sFile, point_t ptRangeA, point_t ptRangeB)
{
	std::string Title("\nMesh generated from " + sFile + ".msh.\nSee " + sFile +".json for details");
	std::string out_datafile(sFile + "_mgl.png");

	// Be careful, this extension must be changed, this line if for test only
	sFile+=".msh";

	mglGraph plot;
	mglData points(sFile.c_str());
	

	//plot.SetSize(1200,900);          ///gr->SetSize(1200,900) Set image size in pixels
	plot.SetSize(900,900);          ///gr->SetSize(900,900) Set image size in pixels
	plot.SetMarkSize(0.5);    /// gr->SetMarkSize(0.0005) Set size of the marker, i.e. the dot size on plot
	
	plot.Alpha(true); plot.Light(true); //plot.Transparent(false);
	
	plot.SetFontSize(4);  /// gr->SetFontSize(4) Sets the global font size for the plot ticks and related

	plot.SetRanges(ptRangeA[0],ptRangeB[0],ptRangeA[1],ptRangeB[1]);
	
	//plot.Axis();
	plot.Aspect(1,1); /// define the aspect ratio for the axis;
	
	//plot.Title(Title.c_str(),"C:iC",8); /// sets the plot title with higher font, the format is "(color):(fontfamily)(alignment)"
	plot.Title(Title.c_str(),"C:iC",5); /// sets the plot title, the format is "(color):(fontfamily)(alignment)"
	plot.Box(); /// Put a bounding box around the plot
	plot.Axis(); /// Show the axis with numbers
	plot.Plot(points.SubData(0),points.SubData(1),"r #o"); 
	
	plot.WritePNG(out_datafile.c_str(),"",false); ///gr->WritePNG(out_datafile.c_str(),"",false) put the plot on a PNG file
	
	return 0;
}
