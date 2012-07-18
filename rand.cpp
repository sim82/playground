#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <math.h>
#include <sys/time.h>
#include <unistd.h>

double gettime(void )
{
#ifdef WIN32
    static bool g_pc_valid = false;
    static LARGE_INTEGER g_pc_freq;

	if( !g_pc_valid ) {
		QueryPerformanceFrequency( &g_pc_freq );
		g_pc_valid = true;
	}
	LARGE_INTEGER pcv;
	QueryPerformanceCounter( &pcv );
	return pcv.QuadPart / double(g_pc_freq.QuadPart);

#else
 struct timeval ttime;
 gettimeofday(&ttime , 0);
 return ttime.tv_sec + ttime.tv_usec * 0.000001;
#endif
}


class timer {
    double m_st;

public:
    timer() : m_st(gettime()) {};

    double elapsed() const {
        return gettime() - m_st;
    }


};

float frand() {
	return std::rand() / float(RAND_MAX);
}

float rand_norm() {
	return sqrt( -2 * log( frand() )) * cos( 2 * M_PI * frand() );
}

int sign( float v ) {
	if( v < 0.0 ) {
		return -1;
	} else {
		return 1;
	}
}

float rand_poisson( float lambda ) {
	float l = exp( - lambda );
	int k = 0;
	float p = 1;


	do {
		++k;

		p = p * frand();
	} while( p > l );

	return k - 1;
}

int main() {


	timer t1;
	float vtime = 0.0;

//	float race = false;
	float last_race = t1.elapsed();
	int race_mode = 0;

	while( true ) {
	//	std::cout << rand_norm() << " " << rand_norm() << "\n";

//		float sd = 5e5;
//
//		float skew = sd * rand_norm();
//		if( skew < 0.0 && skew < -1e6 ) {
//			skew = -1e6;
//		} else if( skew > 0 && skew > 1e6 ) {
//			skew = 1e6;
//		}
//
//
//		std::cout << "bla: " << i << " " << t1.elapsed() << " " << skew << "\n";
//		++i;
//		usleep( 1e6 + skew );


		float step = 1 / 4.0;


		float delta = vtime - t1.elapsed();

		if( race_mode == 0 && t1.elapsed() - last_race > 20.0 ) {
			race_mode = sign(delta);
			last_race = t1.elapsed();
		} else if( sign( delta ) != sign( race_mode )) {
			race_mode = 0;
		}



		float r = rand_poisson(1);


		if( race_mode < 0 ) {

			r = std::max( r - 1, 0.0f );
		} else if( race_mode > 0 ) {
			r += 1.0;
		}

		float t = r * step;

		std::cout << "t: " << vtime << " " << " rm: " << race_mode << " " << t1.elapsed() << " " << t << "\n";
		vtime += step;
		usleep( t * 1e6 );


	}

}
