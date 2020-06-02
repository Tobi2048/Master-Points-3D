#include <iostream>
#include<fstream>
#include <string>
#include <vector>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/io/ply_io.h>
#include <pcl/filters/voxel_grid.h>



typedef struct points_txt
{
	double x;  //mm world coordinate x
	double y;  //mm world coordinate y
	double z;  //mm world coordinate z
	int rgb;


}POINT_WORLD;



int main()
{
	float fakt = 0.45f;
	int number_Txt;
	FILE* fp_txt;
	points_txt TxtPoint;
	std::vector<points_txt> vec_TxtPoints;

	fp_txt = fopen("C:/Users/tobia/Desktop/Master_Arbeit/Point_clouds/Jokari.txt", "r");// hier die txt datei eintragen<--------------------------------<-<-<-<-<-<-<-<-<

	if (fp_txt)//If File open, push points in Vector 
	{
		while (fscanf(fp_txt, "%lf %lf %lf %d", &TxtPoint.x, &TxtPoint.y, &TxtPoint.z, &TxtPoint.rgb) != EOF)
		{
			vec_TxtPoints.push_back(TxtPoint);
		}
	}
	else//wenn Datei nicht geöffnet wurde
		std::cout << "could not open" << std::endl;


	number_Txt = vec_TxtPoints.size();// Anzahl der xyz Punkte 

	//pcl::PointCloud<pcl::PointXYZ> cloud;// Pointcloud Datenformat  in "cloud"
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_vox(new pcl::PointCloud<pcl::PointXYZ>);

	// Fill in the cloud data
	cloud->width = number_Txt;
	cloud->height = 1;
	cloud->is_dense = false;
	cloud->points.resize(cloud->width * cloud->height);


	for (size_t i = 0; i < cloud->points.size(); ++i)// läuft alle Punkte durch und übergibt sie an cloud
	{
		cloud->points[i].x = vec_TxtPoints[i].x;
		cloud->points[i].y = vec_TxtPoints[i].y;
		cloud->points[i].z = vec_TxtPoints[i].z;

	}
	std::cout << " erstelle vox\n";
	// voxel grid erstellen -> Punktdichte verringern
	pcl::VoxelGrid<pcl::PointXYZ> sor;
	sor.setInputCloud(cloud);
	sor.setLeafSize(fakt, fakt, fakt);
	sor.filter(*cloud_vox);
	std::cout << "Vox-Grid erstell faktor:" << fakt << std::endl;


	pcl::io::savePCDFileASCII("C:/Users/tobia/Desktop/Master_Arbeit/Point_clouds/jokari.pcd", *cloud_vox);
	std::cerr << "Saved " << cloud_vox->points.size() << " data points to txt2pcd.pcd." << std::endl;

	std::cout << "erstellt";
	return (0);
}

