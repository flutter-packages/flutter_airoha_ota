/* Copyright Statement:
 *
 * (C) 2020  Airoha Technology Corp. All rights reserved.
 *
 * This software/firmware and related documentation ("Airoha Software") are
 * protected under relevant copyright laws. The information contained herein
 * is confidential and proprietary to Airoha Technology Corp. ("Airoha") and/or its licensors.
 * Without the prior written permission of Airoha and/or its licensors,
 * any reproduction, modification, use or disclosure of Airoha Software,
 * and information contained herein, in whole or in part, shall be strictly prohibited.
 * You may only use, reproduce, modify, or distribute (as applicable) Airoha Software
 * if you have agreed to and been bound by the applicable license agreement with
 * Airoha ("License Agreement") and been granted explicit permission to do so within
 * the License Agreement ("Permitted User").  If you are not a Permitted User,
 * please cease any access or use of Airoha Software immediately.
 * BY OPENING THIS FILE, RECEIVER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
 * THAT AIROHA SOFTWARE RECEIVED FROM AIROHA AND/OR ITS REPRESENTATIVES
 * ARE PROVIDED TO RECEIVER ON AN "AS-IS" BASIS ONLY. AIROHA EXPRESSLY DISCLAIMS ANY AND ALL
 * WARRANTIES, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NONINFRINGEMENT.
 * NEITHER DOES AIROHA PROVIDE ANY WARRANTY WHATSOEVER WITH RESPECT TO THE
 * SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, INCORPORATED IN, OR
 * SUPPLIED WITH AIROHA SOFTWARE, AND RECEIVER AGREES TO LOOK ONLY TO SUCH
 * THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. RECEIVER EXPRESSLY ACKNOWLEDGES
 * THAT IT IS RECEIVER'S SOLE RESPONSIBILITY TO OBTAIN FROM ANY THIRD PARTY ALL PROPER LICENSES
 * CONTAINED IN AIROHA SOFTWARE. AIROHA SHALL ALSO NOT BE RESPONSIBLE FOR ANY AIROHA
 * SOFTWARE RELEASES MADE TO RECEIVER'S SPECIFICATION OR TO CONFORM TO A PARTICULAR
 * STANDARD OR OPEN FORUM. RECEIVER'S SOLE AND EXCLUSIVE REMEDY AND AIROHA'S ENTIRE AND
 * CUMULATIVE LIABILITY WITH RESPECT TO AIROHA SOFTWARE RELEASED HEREUNDER WILL BE,
 * AT AIROHA'S OPTION, TO REVISE OR REPLACE AIROHA SOFTWARE AT ISSUE,
 * OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY RECEIVER TO
 * AIROHA FOR SUCH AIROHA SOFTWARE AT ISSUE.
 */
/* Airoha restricted information */

#ifndef _PEQ_INTERFACE_H_
#define _PEQ_INTERFACE_H_


#ifdef __cplusplus
extern "C" {
#endif

#ifdef _WIN32
    #ifdef CPP_EXPORTS
        #ifdef __GNUC__
            #define DLLEXP __attribute__ ((dllexport))
        #else
            #define DLLEXP __declspec(dllexport)
        #endif
    #else
        #ifdef __GNUC__
            #define DLLEXP __attribute__ ((dllimport))
        #else
            #define DLLEXP __declspec(dllimport)
        #endif
    #endif
#else
    typedef int errno_t;
    #define fopen_s(pFile,filename,mode) ((*(pFile))=fopen((filename),(mode)))==NULL
    #define sprintf_s(dest,len,format,...) sprintf(dest,format,__VA_ARGS__)
    #if __GNUC__ >= 4
        #define DLLEXP __attribute__ ((visibility ("default")))
    #else
        #define DLLEXP
    #endif
#endif


	// calc global z : 48000 or 44100  
	// Need calc at APP lunch , can speed up realtime PEQ
	DLLEXP void calc_z ( double fs);

	// Step1 : set parameters
	//para_limit_en: for 1530 use, 1550 don't care this value
	DLLEXP void setParam(int thread_id, double FS , int total_band , int Mode , int debug, int para_limit_en);
	DLLEXP void set_peq_point(int thread_id, int set, double F, double G, double BW);
	
	//   Type1: Low pass , Type2: High pass,
	DLLEXP void set_xpf_point(int thread_id, int set, double F, double Q , int B0L1H2);

	// Step2 : COFE Generate 
	DLLEXP int generate_cofe(int thread_id);
	DLLEXP double get_freq_resp_max(int thread_id);  // to get Max of freq max

	// Step3 : Apply rescale value
	DLLEXP int change_rescale_cofe(int thread_id , double M_Gain_dB);
	DLLEXP double get_M_Gain_dB_max(int thread_id);  // to get M_Gain_dB_max
	DLLEXP double get_Rescaling_dB(int thread_id);  // to get Rescaling_dB

	// Step4 : freq resp related , get rescale value
	DLLEXP int generate_freq_resp(int thread_id);
	DLLEXP double* get_resp_freq(int thread_id);
	DLLEXP double* get_resp_y(int thread_id);	

	// Step5 : get final COFE
	DLLEXP unsigned short get_cofe_count( int thread_id);
	DLLEXP unsigned short* get_cofe_param( int thread_id);

	// Step6 : free thread
	DLLEXP void destroy (int thread_id);





#ifdef __cplusplus
}
#endif


#endif
