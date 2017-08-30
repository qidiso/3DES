#ifndef VNECT_UTILS
#define VNECT_UTILS
#include "mCaffePredictor.hpp"

// According to the paper, I got that the image is 
// represented by joint angle \theta and camera location d
// I will maintain a bone length array. 
// The length is 3D length  
// Just use the camera coordinate as the world coordinate.
class mVNectUtils: public mCaffePredictor {
protected:
    virtual void preprocess(const cv::Mat & img, std::vector<cv::Mat> * input_data);
    virtual void wrapInputLayer(std::vector<cv::Mat> * input_data);
private:
    double _time_stamp; // used for filter
    bool _is_tracking;
    std::vector<float> _scales;
    cv::Size _box_size; 
    
    bool _is_first_frame;
    std::vector<int> _crop_rect;
    std::vector<int> _pad_offset;
    int _crop_size;
    float _crop_scale;
    // The scale of the input and the output. Now it's 8.
    float _hm_factor; 
    std::vector<std::vector<int> > joints_2d;
    std::vector<std::vector<double> > joints_3d; 
    // Used for fitting! P^G_t P^G_t-1 P^G_t-2 and the same order of global_d
    double * joint_angles[3]; 
    double * global_d[3];

    cv::Mat padImage(const cv::Mat &img, cv::Size box_size);
    std::vector<int> crop_pos(bool type, int crop_offset=0);
    // Used to get the 3d location of all points by \theta and d
    std::vector<std::vector<double> > cal_3dpoints(const double * angles, const double * d);
public:
    ~mVNectUtils();
    mVNectUtils(const std::string &model_path, const std::string &deploy_path, const std::string &mean_path="");
    std::vector<std::vector<int> > predict(const cv::Mat &img, std::vector<std::vector<double> > &joints3d);
};
#endif
