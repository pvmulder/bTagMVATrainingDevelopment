#ifndef CMSSTYLE_HPP
#define CMSSTYLE_HPP

#include <iostream>
#include "TStyle.h"
#include "TH1.h"
#include "TH2.h"
#include "TF1.h"
#include "THStack.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TMath.h"
#include "TLatex.h"
#include "TROOT.h"
#include "TColor.h"

class CMSStyle{

public:

  CMSStyle(){
    //void setTDRStyle() {
    //TStyle *cmsStyle = new TStyle("cmsStyle","Style for P-TDR");
    gROOT->SetStyle("Plain");
    cmsStyle.SetPalette(1);
    cmsStyle.SetPaintTextFormat("4.3f");

    //  cmsStyle.SetTextSize(6);
    
    // For the canvas:
  cmsStyle.SetCanvasBorderMode(0);
  cmsStyle.SetCanvasColor(kWhite);
  cmsStyle.SetCanvasDefH(600); //Height of canvas
  cmsStyle.SetCanvasDefW(800); //Width of canvas
  cmsStyle.SetCanvasDefX(0);   //POsition on screen
  cmsStyle.SetCanvasDefY(0);
 
  // For the Pad:
  cmsStyle.SetPadBorderMode(0);
  cmsStyle.SetPadRightMargin(0.02);
  // cmsStyle.SetPadBorderSize(Width_t size = 1);
  cmsStyle.SetPadColor(kWhite);
  cmsStyle.SetPadGridX(false);
  cmsStyle.SetPadGridY(false);
  cmsStyle.SetGridColor(0);
  cmsStyle.SetGridStyle(3);
  cmsStyle.SetGridWidth(1);

// For the frame:
  cmsStyle.SetFrameBorderMode(0);
  cmsStyle.SetFrameBorderSize(1);
  cmsStyle.SetFrameFillColor(0);
  cmsStyle.SetFrameFillStyle(0);
  cmsStyle.SetFrameLineColor(1);
  cmsStyle.SetFrameLineStyle(1);
  cmsStyle.SetFrameLineWidth(1);

// For the histo:
  // cmsStyle.SetHistFillColor(1);
  // cmsStyle.SetHistFillStyle(0);
  cmsStyle.SetHistLineColor(1);
  cmsStyle.SetHistLineStyle(1);
  cmsStyle.SetHistLineWidth(1);
  // cmsStyle.SetLegoInnerR(Float_t rad = 0.5);
  // cmsStyle.SetNumberContours(Int_t number = 20);

  cmsStyle.SetEndErrorSize(3);
//  cmsStyle.SetErrorMarker(20);
//  cmsStyle.SetErrorX(0.);
  
 // cmsStyle.SetMarkerStyle(20);

//For the fit/function:
  cmsStyle.SetOptFit(1);
  cmsStyle.SetFitFormat("5.4g");
  cmsStyle.SetFuncColor(2);
  cmsStyle.SetFuncStyle(1);
  cmsStyle.SetFuncWidth(1);

//For the date:
  cmsStyle.SetOptDate(0);
  // cmsStyle.SetDateX(Float_t x = 0.01);
  // cmsStyle.SetDateY(Float_t y = 0.01);

// For the statistics box:
  cmsStyle.SetOptFile(0);
  //cmsStyle.SetOptStat("mr"); // To display the mean and RMS:   SetOptStat("mr");
  cmsStyle.SetOptStat(0);
  cmsStyle.SetStatColor(kWhite);
  cmsStyle.SetStatFont(42);
  cmsStyle.SetStatFontSize(0.025);
  cmsStyle.SetStatTextColor(1);
  cmsStyle.SetStatFormat("6.4g");
  cmsStyle.SetStatBorderSize(1);
  cmsStyle.SetStatH(0.5);
  cmsStyle.SetStatW(0.35);
  // cmsStyle.SetStatStyle(Style_t style = 1001);
  // cmsStyle.SetStatX(Float_t x = 0);
  // cmsStyle.SetStatY(Float_t y = 0);

// Margins:
  cmsStyle.SetPadTopMargin(0.05);
  cmsStyle.SetPadBottomMargin(0.16);//default 0.13
  cmsStyle.SetPadLeftMargin(0.16);
  cmsStyle.SetPadRightMargin(0.02);

// For the Global title:

  cmsStyle.SetOptTitle(0);
  cmsStyle.SetTitleFont(42);
  cmsStyle.SetTitleColor(1);
  cmsStyle.SetTitleTextColor(1);
  cmsStyle.SetTitleFillColor(10);
  cmsStyle.SetTitleFontSize(0.05);
  // cmsStyle.SetTitleH(0); // Set the height of the title box
  // cmsStyle.SetTitleW(0); // Set the width of the title box
  // cmsStyle.SetTitleX(0); // Set the position of the title box
  // cmsStyle.SetTitleY(0.985); // Set the position of the title box
  // cmsStyle.SetTitleStyle(Style_t style = 1001);
  // cmsStyle.SetTitleBorderSize(2);

// For the axis titles:

  cmsStyle.SetTitleColor(1, "XYZ");
  cmsStyle.SetTitleFont(42, "XYZ");
  cmsStyle.SetTitleSize(0.06, "XYZ");
  // cmsStyle.SetTitleXSize(Float_t size = 0.02); // Another way to set the size?
  // cmsStyle.SetTitleYSize(Float_t size = 0.02);
  cmsStyle.SetTitleXOffset(1.1);//default 0.9
  //cmsStyle.SetTitleYOffset(1.25);
  cmsStyle.SetTitleYOffset(1.12);
  // cmsStyle.SetTitleOffset(1.1, "Y"); // Another way to set the Offset

// For the axis labels:

  cmsStyle.SetLabelColor(1, "XYZ");
  cmsStyle.SetLabelFont(42, "XYZ");
  cmsStyle.SetLabelOffset(0.007, "XYZ");
  cmsStyle.SetLabelSize(0.05, "XYZ");

// For the axis:

  cmsStyle.SetAxisColor(1, "XYZ");
  cmsStyle.SetStripDecimals(kTRUE);
  cmsStyle.SetTickLength(0.03, "XYZ");
  cmsStyle.SetNdivisions(510, "XYZ");
  cmsStyle.SetPadTickX(1);  // To get tick marks on the opposite side of the frame
  cmsStyle.SetPadTickY(1);

// Change for log plots:
  cmsStyle.SetOptLogx(0);
  cmsStyle.SetOptLogy(0);
  cmsStyle.SetOptLogz(0);

// Postscript options:
  cmsStyle.SetPaperSize(20.,20.);
  // cmsStyle.SetLineScalePS(Float_t scale = 3);
  // cmsStyle.SetLineStyleString(Int_t i, const char* text);
  // cmsStyle.SetHeaderPS(const char* header);
  // cmsStyle.SetTitlePS(const char* pstitle);

  // cmsStyle.SetBarOffset(Float_t baroff = 0.5);
  // cmsStyle.SetBarWidth(Float_t barwidth = 0.5);
  // cmsStyle.SetPaintTextFormat(const char* format = "g");
  // cmsStyle.SetPalette(Int_t ncolors = 0, Int_t* colors = 0);
  // cmsStyle.SetTimeOffset(Double_t toffset);
  // cmsStyle.SetHistMinimumZero(kTRUE);

  cmsStyle.cd();

};

 ~CMSStyle();
						\

  void cd(){
    cmsStyle.cd();
  };

void CMSPreliminary(){
    TLatex* text1 = new TLatex(3.570061,23.08044,"CMS Preliminary");
    text1->SetNDC();
    text1->SetTextAlign(13);
    text1->SetX(0.184);
    text1->SetY(0.928);
    text1->SetTextFont(42);
    text1->SetTextSizePixels(24);
    text1->Draw("same");}

void CMSPreliminary_2D(){
    TLatex* text1 = new TLatex(3.570061,23.08044,"CMS Preliminary");
    text1->SetNDC();
    text1->SetTextAlign(13);
    text1->SetX(0.184);
    text1->SetY(0.988);
    text1->SetTextFont(42);
    text1->SetTextSizePixels(24);
    text1->Draw("same");}

  void TextforCMS(std::string text,float row){ 
  TLatex* text2 = new TLatex(3.570061,23.08044,text.c_str());
  text2->SetNDC();
  text2->SetTextAlign(13);
  text2->SetX(0.184);
  text2->SetY(0.928-row*0.048);
  text2->SetTextFont(42);
  text2->SetTextSizePixels(24);
  text2->Draw("same");}
  
void ShowLumi(std::string lumi){
  //TLatex* text2 = new TLatex(3.570061,23.08044,"11.4 nb^{-1} at #sqrt{s} = 7 TeV");
  lumi += " pb^{-1} at #sqrt{s} = 7 TeV";
  TLatex* text2 = new TLatex(3.570061,23.08044,lumi.c_str());
  text2->SetNDC();
  text2->SetTextAlign(13);
  text2->SetX(0.184);
  text2->SetY(0.88);
  text2->SetTextFont(42);
  text2->SetTextSizePixels(24);
  text2->Draw("same");}
  
// tdrGrid: Turns the grid lines on (true) or off (false)
void tdrGrid(bool gridOn) {
  cmsStyle.SetPadGridX(gridOn);
  cmsStyle.SetPadGridY(gridOn);
}

// fixOverlay: Redraws the axis

void fixOverlay() {
  gPad->RedrawAxis();
}


  void setup_style(TH1* histo, std::string AxisTitle, Color_t lcolor, bool fill, bool stat)
  { 
    histo->SetLineWidth(2);
    
    //histo->SetMinimum(0);
    histo->SetTitle(AxisTitle.c_str());
    //histo->SetMarkerStyle(0); //if activated, blocks the end error bars
    //histo->SetXTitle(xtitle.c_str());
    //histo->SetYTitle(ytitle.c_str());
    if(fill){histo->SetFillColor(lcolor);}
    else{
      histo->SetFillColor(0);
      histo->SetLineColor(lcolor);}

    histo->SetStats(stat);


  }

  void setup_style2(TH1* histo, std::string xtitle, std::string ytitle, int lcolor, bool fill, bool stat)
  { 
    histo->SetLineWidth(2);
    cmsStyle.SetPadRightMargin(0.02);
    histo->SetMinimum(0);
    histo->SetMaximum(1.5*histo->GetMaximum());
    histo->SetXTitle(xtitle.c_str());
    histo->SetYTitle(ytitle.c_str());
    if(fill){histo->SetFillColor(lcolor);}
    else{
      histo->SetFillColor(0);
      histo->SetLineColor(lcolor);}

    histo->SetStats(stat);
    
  }


  void setup_style_2D(TH2* histo, std::string xtitle, std::string ytitle)
  {
    cmsStyle.SetPadRightMargin(0.03);
    histo->SetTitle("");      
    histo->SetXTitle(xtitle.c_str());
    histo->SetYTitle(ytitle.c_str());
    //    histo->SetMinimum(0);

    histo->SetStats(0);
    histo->SetMarkerSize(3);
  }

  void setup_style_data(TH1* histo, std::string AxisTitle, Color_t lcolor, bool fill, bool stat)
  { 
    histo->SetLineWidth(2);
    cmsStyle.SetPadRightMargin(0.02);
    histo->SetMarkerStyle(20);
    histo->SetMarkerSize(0.8);

    histo->SetMinimum(0);
    //histo->SetXTitle(xtitle.c_str());
    //histo->SetYTitle(ytitle.c_str());
    histo->SetTitle(AxisTitle.c_str());
    if(fill){histo->SetFillColor(lcolor);}
    else{
      histo->SetFillColor(0);
      histo->SetLineColor(lcolor);}

    histo->SetStats(stat);


  }


  void overtitle(std::string title){
 TPaveText* text = new TPaveText(0.3,0.95,0.7,1,"brNDC");
    text->SetFillColor(0);
    text->SetTextSizePixels(24);
    //  char line[255];
    //sprintf(line,"A_{C,gen} = %3.6f",ACgen);
    text->AddText(title.c_str());
    text->Draw("same");
}

private:
  TStyle cmsStyle;
    
};

#endif
