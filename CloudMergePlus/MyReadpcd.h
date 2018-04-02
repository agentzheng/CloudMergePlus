#include<fstream>
#include<iostream>
#include <SimpleCloud.h>
#include<string>
#include <pcl/io/pcd_io.h>

namespace MPCR
{
	using namespace std;
	using namespace CCLib;
	
	//һ�����ª�Ķ�ȡPCD�ķ���
	bool MyreadPCD(const string& filename, SimpleCloud& cloud) 
	{
		cloud.clear();
		ifstream ifs(filename, ios::in);
		if (!ifs)
			return false;
		string temp;
		for (int i = 0; i < 9; i++)
		{
			getline(ifs, temp);
		}
		//ǰ����
		ifs >> temp;
		unsigned int size = 0;
		ifs >> size;

		//�����ǵ�ʮ��
		getline(ifs, temp);
		getline(ifs, temp);
		double x = 0, y = 0, z = 0;
		cloud.reserve(size);
		for(int i=0;i<size;i++)
		{
			ifs >> x >> y >> z;
			cout << x << y << z;
			cloud.addPoint(CCVector3(x, y, z));
		}
		ifs.close();
		return true;

	}

	bool MyWritePCD(const string& filename, SimpleCloud& cloud)
	{
		ofstream ofs(filename, ios::out);
		if (!ofs)
			return false;
		ofs<<"# .PCD v0.7 - Point Cloud Data file format"<<endl;
		ofs << "VERSION 0.7" << endl;
		ofs << "FIELDS x y z" << endl;
		ofs << "SIZE 4 4 4" << endl;
		ofs << "TYPE F F F" << endl;
		ofs << "COUNT 1 1 1" << endl; 
		ofs << "WIDTH "<< cloud.size() << endl;
		ofs << "HEIGHT 1" << endl;
		ofs << "VIEWPOINT 0 0 0 1 0 0 0" << endl;
		ofs << "POINTS "<<cloud.size() << endl;
		ofs << "DATA ascii" << endl;
		for (unsigned int i = 0; i < cloud.size(); i++)
		{
			const CCVector3* v=cloud.getPoint(i);
			ofs << v->x << ' ' << v->y << ' ' << v->z << endl;
		}
		ofs.close();
		return true;
	}

	bool readPCD(string filename, pcl::PointCloud<pcl::PointXYZ>& cloud)
	{
		cloud.clear();
		if (pcl::io::loadPCDFile<pcl::PointXYZ>(filename, cloud) == -1) //* ����PCD��ʽ���ļ�������ļ������ڣ�����-1  
		{
			PCL_ERROR("Couldn't read file test_pcd.pcd \n"); //�ļ�������ʱ�����ش�����ֹ����  
			return false;
		}
		return true;
	}


	void writePCD(string filename, pcl::PointCloud<pcl::PointXYZ>& cloud)
	{
		pcl::io::savePCDFileASCII(filename, cloud); //�����Ʊ��浽PCD�ļ���
	}






};