/*
 * Copyright (C) 2011 Simon A. Berger
 * 
 *  This program is free software; you may redistribute it and/or modify its
 *  under the terms of the GNU General Public License as published by the Free
 *  Software Foundation; either version 2 of the License, or (at your option)
 *  any later version.
 *
 *  This program is distributed in the hope that it will be useful, but
 *  WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 *  or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 *  for more details.
 */


#include <cstdio>
#include <cerrno>
#include <unistd.h>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <math.h>

#include <vector>
#include <iostream>
#include <algorithm>
#include <jack/jack.h>


namespace fast {
// fast sin/cos.
// shamelessly ripped from http://www.flipcode.com/archives/Fast_Trigonometry_Functions_Using_Lookup_Tables.shtml
    
const static int MAX_CIRCLE_ANGLE = 512;
const static int HALF_MAX_CIRCLE_ANGLE = MAX_CIRCLE_ANGLE / 2;
const static int QUARTER_MAX_CIRCLE_ANGLE  = MAX_CIRCLE_ANGLE / 4;
const static int MASK_MAX_CIRCLE_ANGLE = MAX_CIRCLE_ANGLE - 1;
const float PI = 3.14159265358979323846f;

static float fast_cossin_table[MAX_CIRCLE_ANGLE];           // Declare table of fast cosinus and sinus

// Copied from NVidia web site
inline void FloatToInt(int *int_pointer, float f) 
{
//     __asm  fld  f
//   __asm  mov  edx,int_pointer
//   __asm  FRNDINT
//   __asm  fistp dword ptr [edx];
    *int_pointer = f;

}

inline float cos(float n)
{
   float f = n * HALF_MAX_CIRCLE_ANGLE / PI;
   int i;
   FloatToInt(&i, f);
   if (i < 0)
   {
      return fast_cossin_table[((-i) + QUARTER_MAX_CIRCLE_ANGLE)&MASK_MAX_CIRCLE_ANGLE];
   }
   else
   {
      return fast_cossin_table[(i + QUARTER_MAX_CIRCLE_ANGLE)&MASK_MAX_CIRCLE_ANGLE];
   }

   assert(0);
}

inline float sin(float n)
{
   float f = n * HALF_MAX_CIRCLE_ANGLE / PI;
   int i;
   
   FloatToInt(&i, f);
   
//    std::cout << "f: " << f << " " << i << "\n";
   
   float v;
   if (i < 0)
   {
      v = fast_cossin_table[(-((-i)&MASK_MAX_CIRCLE_ANGLE)) + MAX_CIRCLE_ANGLE];
   }
   else
   {
      v = fast_cossin_table[i&MASK_MAX_CIRCLE_ANGLE];
   }

//    std::cout << "sin: " << n << " " << v << " " << ::sin(n) << "\n";
//    assert(0);
   
   return v;
}
  
void init() {
    for ( int i = 0 ; i < MAX_CIRCLE_ANGLE ; i++)
    {
        fast_cossin_table[i] = (float)::sin((double)i * PI / HALF_MAX_CIRCLE_ANGLE);
    }
}
    
};


jack_port_t *input_port;
jack_port_t *output_port;
jack_client_t *client;


typedef jack_default_audio_sample_t sample_t;

class osc_sin {
    float m_freq;
    int m_per;
    const static int rate = 44100; 
    float m_gain;
    bool m_invert;
public:
    osc_sin( float freq, float gain, bool invert ) 
    : m_freq(freq), m_per(0), m_gain(gain), m_invert(invert) {}
    
    void render( sample_t *buf, int nframes ) {
        float spp = rate / m_freq;
        
        for( int i = 0; i < nframes; ++i ) {
            float v = m_gain * fast::sin( (i + m_per) / spp * (2 * 3.1415) );
            
            if( false && m_invert ) {
                buf[i] -= v;
            } else {
                buf[i] += v;
            }
        }
        
        m_per += nframes;
        
        //std::cout << "render: " << m_freq << "\n";
        
//         if( m_per > spp ) {
//             m_per -= spp;
//         }
//         
    }

    
};


class osc_sin_harm {
    float m_base_freq;
    int m_per;
    const static int rate = 44100; 
    float m_base_gain;
    float m_attn;
    float m_harm;
public:
    osc_sin_harm( float freq, float gain, float attn, float harm ) 
    : m_base_freq(freq), m_per(0), m_base_gain(gain), m_attn(attn), m_harm(harm) {}
    
    
    void render( sample_t *buf, int nframes ) {
            
        for( int h = 1; h < 20; h += m_harm ) {
            
            float freq = m_base_freq * h;
            float spp = rate / freq;
            std::cout << "freq: " << h << " " << freq << " " << spp << "\n";
        
            for( int i = 0; i < nframes; ++i ) {
        
                buf[i] += (m_base_gain / pow(h,m_attn)) * fast::sin( (i + m_per) / spp * (2 * 3.1415) );
                
//                 buf[i] += 0.5 * fast::sin( (i + m_per) / spp * (2 * 3.1415) );
            }    
            
        }
        
        m_per += nframes;
        
        //std::cout << "render: " << m_freq << "\n";
        
//         if( m_per > spp ) {
//             m_per -= spp;
//         }
//         
    }


    
};

//static osc_sin osc1(440);

std::vector<osc_sin_harm> oscs;

/**
 * The process callback for this JACK application is called in a
 * special realtime thread once for each audio cycle.
 *
 * This client does nothing more than copy data from its input
 * port to its output port. It will exit when stopped by 
 * the user (e.g. using Ctrl-C on a unix-ish operating system)
 */
int process (jack_nframes_t nframes, void *arg)
{
    jack_default_audio_sample_t *in, *out;
    
    in = (jack_default_audio_sample_t *)jack_port_get_buffer (input_port, nframes);
    out = (jack_default_audio_sample_t *)jack_port_get_buffer (output_port, nframes);
    memcpy (out, in,
        sizeof (jack_default_audio_sample_t) * nframes);

//     osc1.render(out, nframes);
    
    for( auto &osc : oscs ) {
        osc.render( out, nframes );
    }
//     
//     std::for_each(oscs.begin(), oscs.end(), [&]( osc_sin_harm &osc ) {
//         osc.render( out, nframes );
//         
//     }
//     );
//     
    return 0;      
}

/**
 * JACK calls this shutdown_callback if the server ever shuts down or
 * decides to disconnect the client.
 */
void
jack_shutdown (void *arg)
{
    exit (1);
}


void init_osc() {
 
    int base_freq = 440;

    oscs.push_back(osc_sin_harm(base_freq, 0.5, 1, 1));
    
// //     float gain = 0.5;
//     
//     for( int i = 1; i < 40; i += 2 ) {
//             
//         
// //         gain = std::max(0.0f,gain);
//         float gain = 1/pow(i,1.0);
//         
//         oscs.push_back( osc_sin( base_freq * i, gain, i % 2 == 0 )); 
//     
//         std::cout << "gain: " << base_freq * i << " " << gain << "\n"; 
// //         gain *= 0.70;
//     }
    
}

int
main (int argc, char *argv[])
{
    const char **ports;
    const char *client_name = "simple";
    const char *server_name = NULL;
    jack_options_t options = JackNullOption;
    jack_status_t status;
    
    fast::init();
    
    /* open a client connection to the JACK server */

    client = jack_client_open (client_name, options, &status, server_name);
    if (client == NULL) {
        fprintf (stderr, "jack_client_open() failed, "
             "status = 0x%2.0x\n", status);
        if (status & JackServerFailed) {
            fprintf (stderr, "Unable to connect to JACK server\n");
        }
        exit (1);
    }
    if (status & JackServerStarted) {
        fprintf (stderr, "JACK server started\n");
    }
    if (status & JackNameNotUnique) {
        client_name = jack_get_client_name(client);
        fprintf (stderr, "unique name `%s' assigned\n", client_name);
    }

    /* tell the JACK server to call `process()' whenever
       there is work to be done.
    */

    jack_set_process_callback (client, process, 0);

    /* tell the JACK server to call `jack_shutdown()' if
       it ever shuts down, either entirely, or if it
       just decides to stop calling us.
    */

    jack_on_shutdown (client, jack_shutdown, 0);

    /* display the current sample rate. 
     */

    printf ("engine sample rate: %d \n",
        jack_get_sample_rate (client));

    /* create two ports */

    input_port = jack_port_register (client, "input",
                     JACK_DEFAULT_AUDIO_TYPE,
                     JackPortIsInput, 0);
    output_port = jack_port_register (client, "output",
                      JACK_DEFAULT_AUDIO_TYPE,
                      JackPortIsOutput, 0);

    if ((input_port == NULL) || (output_port == NULL)) {
        fprintf(stderr, "no more JACK ports available\n");
        exit (1);
    }

    
    init_osc();
    
    /* Tell the JACK server that we are ready to roll.  Our
     * process() callback will start running now. */

    if (jack_activate (client)) {
        fprintf (stderr, "cannot activate client");
        exit (1);
    }

    /* Connect the ports.  You can't do this before the client is
     * activated, because we can't make connections to clients
     * that aren't running.  Note the confusing (but necessary)
     * orientation of the driver backend ports: playback ports are
     * "input" to the backend, and capture ports are "output" from
     * it.
     */

    ports = jack_get_ports (client, NULL, NULL,
                JackPortIsPhysical|JackPortIsOutput);
    if (ports == NULL) {
        fprintf(stderr, "no physical capture ports\n");
        exit (1);
    }

    if (jack_connect (client, ports[0], jack_port_name (input_port))) {
        fprintf (stderr, "cannot connect input ports\n");
    }

    free (ports);
    
    ports = jack_get_ports( client, "jamin", NULL, 0 );
    
//     ports = jack_get_ports (client, NULL, NULL, JackPortIsPhysical|JackPortIsInput);
    if (ports == NULL) {
        fprintf(stderr, "no physical playback ports\n");
        exit (1);
    }

    if (jack_connect (client, jack_port_name (output_port), ports[0])) {
        fprintf (stderr, "cannot connect output ports\n");
    }

    free (ports);

    /* keep running until stopped by the user */

    sleep (-1);

    /* this is never reached but if the program
       had some other way to exit besides being killed,
       they would be important to call.
    */

    jack_client_close (client);
    exit (0);
}
