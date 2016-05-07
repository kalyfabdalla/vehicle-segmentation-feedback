#ifndef BACKGROUND_ESTIMATOR_HPP_
#define BACKGROUND_ESTIMATOR_HPP_

#define BOOST_PYTHON_MAX_ARITY 25

#include <stdlib.h>
#include <memory.h>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/opencv_modules.hpp>
#include <boost/python.hpp>
#include <boost/numpy.hpp>

using namespace boost::python;

namespace p = boost::python;
namespace np = boost::numpy;

using namespace cv;

typedef struct PixelGMMZ
{
	float sigma;
	float muR;
	float muG;
	float muB;
	float weight;
}PixelGMMZ;

//*/
class PixelBackgroundModel : public cv::ParallelLoopBody
{
private:
	float fAlphaT;
	float fTb;
	float fTg;
	float fTB;
	float fSigma;
	float fCT;
	float fDnorm;
	int nM;
	bool bShadowDetection;
	float fTau;
	int nNBands;
	int nWidth;
	int nHeight;
	int nSize;
	PixelGMMZ* rGMM;
	unsigned char* rnUsedModes;
	bool bRemoveForeground;
	unsigned char * data;
	unsigned char * output;
	float * values;

	int line;
	void operator ()(const cv::Range& range) const;

public:
	int roi_x;
	int roi_y;
	int roi_width;
	int roi_height;

	PixelBackgroundModel();

	PixelBackgroundModel(float fAlphaT, float fTb, float fTg, float fTB, float fSigma, float fCT, float fDnorm, int nM,
							bool bShadowDetection, float fTau, int nNBands, int nWidth, int nHeight, int nSize,
							bool bRemoveForeground );

	void setRoi(int x, int y, int width, int height) ;

	void backgroundModel(void* data, void* output, void* values);

	void wrapBackgroundModel(np::ndarray & data, np::ndarray & output, np::ndarray & values);

};

#endif
