#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/visualization/cloud_viewer.h>
#include <pcl/filters/radius_outlier_removal.h>
#include <pcl/filters/conditional_removal.h>
#include <vector>

int user_data = 0;
int
main (int argc, char** argv)
{
  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZ>);
  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_filtered (new pcl::PointCloud<pcl::PointXYZ>);

  pcl::io::loadPCDFile ("/home/benlee/Desktop/pc_practice/pcd_files/data/table_scene_lms400.pcd", *cloud);
  if (!cloud->is_dense)
  {
    cloud->is_dense = false;
    std::vector<int> indices;
    pcl::removeNaNFromPointCloud(*cloud,*cloud, indices);
  }
  pcl::RadiusOutlierRemoval<pcl::PointXYZ> outrem;
  outrem.setInputCloud(cloud);
  outrem.setRadiusSearch(0.05);
  outrem.setMinNeighborsInRadius(50);
  outrem.setKeepOrganized(true);
  outrem.filter (*cloud_filtered);

  pcl::visualization::CloudViewer viewer("Cloud Viewer");
  viewer.showCloud(cloud_filtered);
  while (!viewer.wasStopped ())
  {
      user_data++;
  }
  return 0;
}