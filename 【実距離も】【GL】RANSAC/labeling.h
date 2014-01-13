00001// 
00002 // Copyright (c) 2003-2009, MIST Project, Intelligent Media Integration COE, Nagoya University
00003 // All rights reserved.
00004 // 
00005 // Redistribution and use in source and binary forms, with or without modification,
00006 // are permitted provided that the following conditions are met:
00007 // 
00008 // 1. Redistributions of source code must retain the above copyright notice,
00009 // this list of conditions and the following disclaimer.
00010 // 
00011 // 2. Redistributions in binary form must reproduce the above copyright notice,
00012 // this list of conditions and the following disclaimer in the documentation
00013 // and/or other materials provided with the distribution.
00014 // 
00015 // 3. Neither the name of the Nagoya University nor the names of its contributors
00016 // may be used to endorse or promote products derived from this software
00017 // without specific prior written permission.
00018 // 
00019 // THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR
00020 // IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
00021 // FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
00022 // CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
00023 // DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
00024 // DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER
00025 // IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF
00026 // THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
00027 // 
00028 
00037 
00038 #ifndef __INCLUDE_MIST_LABELING__
00039 #define __INCLUDE_MIST_LABELING__
00040 
00041 #ifndef __INCLUDE_MIST_H__
00042 #include "../mist.h"
00043 #endif
00044 
00045 #ifndef __INCLUDE_MIST_LIMITS__
00046 #include "../limits.h"
00047 #endif
00048 
00049 #include <vector>
00050 #include <list>
00051 
00052 
00053 
00054 // mist名前空間の始まり
00055 _MIST_BEGIN
00056 
00057 
00058 namespace __labeling_controller__
00059 {
00060     template < class T > struct default_label_num2
00061     {
00062         _MIST_CONST( size_t, value, 2560 );
00063     };
00064     template < > struct default_label_num2< char >
00065     {
00066         _MIST_CONST( size_t, value, 127 );
00067     };
00068     template < > struct default_label_num2< signed char >
00069     {
00070         _MIST_CONST( size_t, value, 127 );
00071     };
00072     template < > struct default_label_num2< unsigned char >
00073     {
00074         _MIST_CONST( size_t, value, 255 );
00075     };
00076 
00077     template < class T > struct default_label_num3
00078     {
00079         _MIST_CONST( size_t, value, 10000 );
00080     };
00081     template < > struct default_label_num3< char >
00082     {
00083         _MIST_CONST( size_t, value, 127 );
00084     };
00085     template < > struct default_label_num3< signed char >
00086     {
00087         _MIST_CONST( size_t, value, 127 );
00088     };
00089     template < > struct default_label_num3< unsigned char >
00090     {
00091         _MIST_CONST( size_t, value, 255 );
00092     };
00093 
00094 
00095     template < int nc >
00096     struct neighbors
00097     {
00098         _MIST_CONST( size_t, array_num, 13 );
00099 
00100         template < class Array, class Vector >
00101         static inline typename Array::size_type neighbor( Array &in, const Vector &T, typename Vector::value_type *L,
00102                                         const typename Array::size_type i, const typename Array::size_type j, const typename Array::size_type k,
00103                                         const typename Array::size_type w, const typename Array::size_type h, const typename Array::size_type d )
00104         {
00105             typedef typename Array::size_type size_type;
00106 
00107             L[  0 ] =                           k > 0 ? T[ static_cast< size_type >( in( i    , j    , k - 1 ) ) ] : 0;
00108             L[  1 ] =              j     > 0          ? T[ static_cast< size_type >( in( i    , j - 1, k     ) ) ] : 0;
00109             L[  2 ] = i     > 0                       ? T[ static_cast< size_type >( in( i - 1, j    , k     ) ) ] : 0;
00110             L[  3 ] =              j     > 0 && k > 0 ? T[ static_cast< size_type >( in( i    , j - 1, k - 1 ) ) ] : 0;
00111             L[  4 ] = i     > 0 &&              k > 0 ? T[ static_cast< size_type >( in( i - 1, j    , k - 1 ) ) ] : 0;
00112             L[  5 ] = i + 1 < w &&              k > 0 ? T[ static_cast< size_type >( in( i + 1, j    , k - 1 ) ) ] : 0;
00113             L[  6 ] =              j + 1 < h && k > 0 ? T[ static_cast< size_type >( in( i    , j + 1, k - 1 ) ) ] : 0;
00114             L[  7 ] = i     > 0 && j     > 0          ? T[ static_cast< size_type >( in( i - 1, j - 1, k     ) ) ] : 0;
00115             L[  8 ] = i + 1 < w && j     > 0          ? T[ static_cast< size_type >( in( i + 1, j - 1, k     ) ) ] : 0;
00116             L[  9 ] = i     > 0 && j     > 0 && k > 0 ? T[ static_cast< size_type >( in( i - 1, j - 1, k - 1 ) ) ] : 0;
00117             L[ 10 ] = i + 1 < w && j     > 0 && k > 0 ? T[ static_cast< size_type >( in( i + 1, j - 1, k - 1 ) ) ] : 0;
00118             L[ 11 ] = i     > 0 && j + 1 < h && k > 0 ? T[ static_cast< size_type >( in( i - 1, j + 1, k - 1 ) ) ] : 0;
00119             L[ 12 ] = i + 1 < w && j + 1 < h && k > 0 ? T[ static_cast< size_type >( in( i + 1, j + 1, k - 1 ) ) ] : 0;
00120 
00121             return( 0 );
00122         }
00123     };
00124 
00125     template < >
00126     struct neighbors< 18 >
00127     {
00128         _MIST_CONST( size_t, array_num, 9 );
00129 
00130         template < class Array, class Vector >
00131         static inline typename Array::size_type neighbor( Array &in, const Vector &T, typename Vector::value_type *L,
00132                                         const typename Array::size_type i, const typename Array::size_type j, const typename Array::size_type k,
00133                                         const typename Array::size_type w, const typename Array::size_type h, const typename Array::size_type d )
00134         {
00135             typedef typename Array::size_type size_type;
00136 
00137             L[  0 ] =                           k > 0 ? T[ static_cast< size_type >( in( i    , j    , k - 1 ) ) ] : 0;
00138             L[  1 ] =              j     > 0          ? T[ static_cast< size_type >( in( i    , j - 1, k     ) ) ] : 0;
00139             L[  2 ] = i     > 0                       ? T[ static_cast< size_type >( in( i - 1, j    , k     ) ) ] : 0;
00140             L[  3 ] =              j     > 0 && k > 0 ? T[ static_cast< size_type >( in( i    , j - 1, k - 1 ) ) ] : 0;
00141             L[  4 ] = i     > 0 &&              k > 0 ? T[ static_cast< size_type >( in( i - 1, j    , k - 1 ) ) ] : 0;
00142             L[  5 ] = i + 1 < w &&              k > 0 ? T[ static_cast< size_type >( in( i + 1, j    , k - 1 ) ) ] : 0;
00143             L[  6 ] =              j + 1 < h && k > 0 ? T[ static_cast< size_type >( in( i    , j + 1, k - 1 ) ) ] : 0;
00144             L[  7 ] = i     > 0 && j     > 0          ? T[ static_cast< size_type >( in( i - 1, j - 1, k     ) ) ] : 0;
00145             L[  8 ] = i + 1 < w && j     > 0          ? T[ static_cast< size_type >( in( i + 1, j - 1, k     ) ) ] : 0;
00146 
00147             return( 0 );
00148         }
00149     };
00150 
00151     template < >
00152     struct neighbors< 6 >
00153     {
00154         _MIST_CONST( size_t, array_num, 3 );
00155 
00156         template < class Array, class Vector >
00157         static inline typename Array::size_type neighbor( Array &in, const Vector &T, typename Vector::value_type *L,
00158                                         const typename Array::size_type i, const typename Array::size_type j, const typename Array::size_type k,
00159                                         const typename Array::size_type w, const typename Array::size_type h, const typename Array::size_type d )
00160         {
00161             typedef typename Array::size_type size_type;
00162 
00163             L[  0 ] =                           k > 0 ? T[ static_cast< size_type >( in( i    , j    , k - 1 ) ) ] : 0;
00164             L[  1 ] =              j     > 0          ? T[ static_cast< size_type >( in( i    , j - 1, k     ) ) ] : 0;
00165             L[  2 ] = i     > 0                       ? T[ static_cast< size_type >( in( i - 1, j    , k     ) ) ] : 0;
00166 
00167             return( 0 );
00168         }
00169     };
00170 
00171     template < >
00172     struct neighbors< 8 >
00173     {
00174         _MIST_CONST( size_t, array_num, 4 );
00175 
00176         template < class Array, class Vector >
00177         static inline typename Array::size_type neighbor( Array &in, const Vector &T, typename Vector::value_type *L,
00178                                         const typename Array::size_type i, const typename Array::size_type j, const typename Array::size_type k,
00179                                         const typename Array::size_type w, const typename Array::size_type h, const typename Array::size_type d )
00180         {
00181             typedef typename Array::size_type size_type;
00182 
00183             L[ 0 ] = i     > 0 && j > 0 ? T[ static_cast< size_type >( in( i - 1, j - 1 ) ) ] : 0;
00184             L[ 1 ] =              j > 0 ? T[ static_cast< size_type >( in( i    , j - 1 ) ) ] : 0;
00185             L[ 2 ] = i + 1 < w && j > 0 ? T[ static_cast< size_type >( in( i + 1, j - 1 ) ) ] : 0;
00186             L[ 3 ] = i     > 0          ? T[ static_cast< size_type >( in( i - 1, j     ) ) ] : 0;
00187 
00188             return( 0 );
00189         }
00190     };
00191 
00192     template < >
00193     struct neighbors< 4 >
00194     {
00195         _MIST_CONST( size_t, array_num, 2 );
00196 
00197         template < class Array, class Vector >
00198         static inline typename Array::size_type neighbor( Array &in, const Vector &T, typename Vector::value_type *L,
00199                                         const typename Array::size_type i, const typename Array::size_type j, const typename Array::size_type k,
00200                                         const typename Array::size_type w, const typename Array::size_type h, const typename Array::size_type d )
00201         {
00202             typedef typename Array::size_type size_type;
00203 
00204             L[ 0 ] = j > 0 ? T[ static_cast< size_type >( in( i    , j - 1 ) ) ] : 0;
00205             L[ 1 ] = i > 0 ? T[ static_cast< size_type >( in( i - 1, j     ) ) ] : 0;
00206 
00207             return( 0 );
00208         }
00209     };
00210 
00211 
00212     template < class Array, class neighbor, class Functor >
00213     typename Array::size_type labeling( Array &in, typename Array::size_type label_max, const neighbor dmy, Functor f )
00214     {
00215         typedef typename Array::size_type size_type;
00216         typedef typename Array::difference_type difference_type;
00217         typedef typename Array::value_type value_type;
00218 
00219 //      typedef difference_type label_value_type;
00220 //      typedef size_type label_value_type;
00221         typedef unsigned int label_value_type;
00222 
00223         typedef std::vector< label_value_type >::value_type vector_label_value_type;
00224         typedef std::list< label_value_type > label_list_type;
00225 
00226         size_type label_num = 0;
00227         size_type i, j, k, l, count;
00228 
00229         std::vector< label_value_type > T;
00230         std::vector< label_list_type > TBL;
00231         label_value_type L[ neighbor::array_num ];
00232         const size_type width = in.width( );
00233         const size_type height = in.height( );
00234         const size_type depth = in.depth( );
00235 
00236         T.reserve( label_max );
00237         T.push_back( 0 );   // T[ 0 ]
00238         TBL.push_back( label_list_type( ) );    // T[ 0 ]
00239 
00240         const bool bprogress1 = depth == 1;
00241         const bool bprogress2 = depth >  1;
00242 
00243         if( is_float< value_type >::value )
00244         {
00245             label_max = type_limits< size_type >::maximum( );
00246         }
00247         else
00248         {
00249             label_max = static_cast< size_type >( type_limits< value_type >::maximum( ) );
00250         }
00251 
00252         f( 0.0 );
00253 
00254         for( k = 0 ; k < depth ; k++ )
00255         {
00256             for( j = 0 ; j < height ; j++ )
00257             {
00258                 for( i = 0 ; i < width ; i++ )
00259                 {
00260                     // 0画素はラベリングしない
00261                     if( in( i, j, k ) == 0 )
00262                     {
00263                         continue;
00264                     }
00265 
00266                     // 操作済みの要素のラベルを取得する
00267                     neighbor::neighbor( in, T, L, i, j, k, width, height, depth );
00268 
00269                     // 近傍で最小のラベル番号を持つものを取得し，ラベル番号が0で無い物の数を数え上げる
00270                     label_value_type L1 = static_cast< label_value_type >( label_max );
00271                     for( l = 0, count = 0 ; l < neighbor::array_num ; l++ )
00272                     {
00273                         if( L[ l ] > 0 )
00274                         {
00275                             if( L1 != L[ l ] )
00276                             {
00277                                 count++;
00278                             }
00279                             if( L1 > L[ l ] )
00280                             {
00281                                 L1 = L[ l ];
00282                             }
00283                         }
00284                     }
00285 
00286                     if( count == 0 )
00287                     {
00288                         // 近傍に，すでに割り当てられているラベルは存在しないため，新規にラベルを割り当てる
00289                         // 出力ラベル値が出力データ型の最大値を超えなければ，ラベル数を更新する
00290                         if( label_num < label_max )
00291                         {
00292                             label_num++;
00293                         }
00294 
00295                         T.push_back( static_cast< label_value_type >( label_num ) );
00296 
00297                         label_list_type ll;
00298                         ll.push_back( static_cast< label_value_type >( label_num ) );
00299                         TBL.push_back( ll );
00300 
00301                         in( i, j, k ) = static_cast< value_type >( label_num );
00302                     }
00303                     else if( count == 1 )
00304                     {
00305                         // 近傍に，割り当てられているラベルが1つしか存在しないため，そのラベルを割り当てる
00306                         in( i, j, k ) = static_cast< value_type >( L1 );
00307                     }
00308                     else
00309                     {
00310                         in( i, j, k ) = static_cast< value_type >( L1 );
00311 
00312                         // 複数のラベルが結合するため，テーブルを修正する
00313                         for( l = 0 ; l < neighbor::array_num ; l++ )
00314                         {
00315                             label_value_type L0 = L[ l ];
00316                             if( T[ L0 ] != L1 )
00317                             {
00318                                 typename label_list_type::iterator ite  = TBL[ L0 ].begin( );
00319                                 typename label_list_type::iterator eite = TBL[ L0 ].end( );
00320 
00321                                 for( ; ite != eite ; ++ite )
00322                                 {
00323                                     T[ *ite ] = static_cast< vector_label_value_type >( L1 );
00324                                 }
00325 
00326                                 label_list_type &TBL1 = TBL[ L0 ];
00327                                 TBL[ L1 ].insert( TBL[ L1 ].end( ), TBL[ L0 ].begin( ), TBL[ L0 ].end( ) );
00328                                 TBL[ L0 ].clear( );
00329                             }
00330                         }
00331                     }
00332                 }
00333 
00334                 if( bprogress1 )
00335                 {
00336                     f( static_cast< double >( j + 1 ) / static_cast< double >( height ) * 100.0 );
00337                 }
00338             }
00339 
00340             if( bprogress2 )
00341             {
00342                 f( static_cast< double >( k + 1 ) / static_cast< double >( depth ) * 100.0 );
00343             }
00344         }
00345 
00346         f( 100.0 );
00347 
00348         // ラベルの振り直しを行う
00349         size_type *NT = new size_type[ label_num + 1 ];
00350         for( i = 0 ; i <= label_num ; i++ )
00351         {
00352             NT[ i ] = 0;
00353         }
00354 
00355         // 使用しているラベルをチェックする
00356         for( i = 1 ; i <= label_num ; i++ )
00357         {
00358             NT[ T[ i ] ] = 1;
00359         }
00360 
00361         // 使用しているラベルをチェックする
00362         for( i = 1, count = 1 ; i <= label_num ; i++ )
00363         {
00364             if( NT[ i ] != 0 )
00365             {
00366                 NT[ i ] = count++;
00367             }
00368         }
00369 
00370         label_num = 0;
00371         for( i = 0 ; i < in.size( ) ; i++ )
00372         {
00373             if( in[ i ] == 0 )
00374             {
00375                 continue;
00376             }
00377 
00378             size_type label = NT[ T[ static_cast< size_type >( in[ i ] ) ] ];
00379             in[ i ] = static_cast< value_type >( label );
00380             if( label_num < label )
00381             {
00382                 label_num = label;
00383             }
00384         }
00385 
00386         f( 100.1 );
00387 
00388         delete [] NT;
00389 
00390         return( label_num );
00391     }
00392 }
00393 
00394 
00395 
00396 
00404 
00405 
00424 template < class T1, class T2, class Allocator1, class Allocator2, class Functor >
00425 typename array2< T2, Allocator2 >::size_type labeling4( const array2< T1, Allocator1 > &in, array2< T2, Allocator2 > &out, typename array2< T2, Allocator2 >::size_type max_label, Functor f )
00426 {
00427     typedef typename array2< T2, Allocator2 >::size_type  size_type;
00428     typedef typename array2< T2, Allocator2 >::value_type value_type;
00429 
00430     if( max_label == 0 )
00431     {
00432         if( is_float< value_type >::value )
00433         {
00434             max_label = type_limits< size_type >::maximum( );
00435         }
00436         else
00437         {
00438             max_label = static_cast< size_type >( type_limits< value_type >::maximum( ) );
00439         }
00440     }
00441 
00442     out.resize( in.size1( ), in.size2( ) );
00443     out.reso1( in.reso1( ) );
00444     out.reso2( in.reso2( ) );
00445 
00446     for( size_type i = 0 ; i < in.size( ) ; i++ )
00447     {
00448         out[ i ] = static_cast< value_type >( in[ i ] > 0 ? 1 : 0 );
00449     }
00450     return( __labeling_controller__::labeling( out, max_label, __labeling_controller__::neighbors< 4 >( ), f ) );
00451 }
00452 
00453 
00471 template < class T1, class T2, class Allocator1, class Allocator2 >
00472 typename array2< T2, Allocator2 >::size_type labeling4( const array2< T1, Allocator1 > &in, array2< T2, Allocator2 > &out, typename array2< T2, Allocator2 >::size_type max_label = __labeling_controller__::default_label_num2< T2 >::value )
00473 {
00474     return( labeling4( in, out, max_label, __mist_dmy_callback__( ) ) );
00475 }
00476 
00477 
00496 template < class T1, class T2, class Allocator1, class Allocator2, class Functor >
00497 typename array2< T2, Allocator2 >::size_type labeling8( const array2< T1, Allocator1 > &in, array2< T2, Allocator2 > &out, typename array2< T2, Allocator2 >::size_type max_label, Functor f )
00498 {
00499     typedef typename array2< T2, Allocator2 >::size_type  size_type;
00500     typedef typename array2< T2, Allocator2 >::value_type value_type;
00501 
00502     if( max_label == 0 )
00503     {
00504         if( is_float< value_type >::value )
00505         {
00506             max_label = type_limits< size_type >::maximum( );
00507         }
00508         else
00509         {
00510             max_label = static_cast< size_type >( type_limits< value_type >::maximum( ) );
00511         }
00512     }
00513 
00514     out.resize( in.size1( ), in.size2( ) );
00515     out.reso1( in.reso1( ) );
00516     out.reso2( in.reso2( ) );
00517 
00518     for( size_type i = 0 ; i < in.size( ) ; i++ )
00519     {
00520         out[ i ] = static_cast< value_type >( in[ i ] > 0 ? 1 : 0 );
00521     }
00522     return( __labeling_controller__::labeling( out, max_label, __labeling_controller__::neighbors< 8 >( ), f ) );
00523 }
00524 
00525 
00543 template < class T1, class T2, class Allocator1, class Allocator2 >
00544 inline typename array2< T2, Allocator2 >::size_type labeling8( const array2< T1, Allocator1 > &in, array2< T2, Allocator2 > &out, typename array2< T2, Allocator2 >::size_type max_label = __labeling_controller__::default_label_num2< T2 >::value )
00545 {
00546     return( labeling8( in, out, max_label, __mist_dmy_callback__( ) ) );
00547 }
00548 
00549 
00568 template < class T1, class T2, class Allocator1, class Allocator2, class Functor >
00569 typename array3< T2, Allocator2 >::size_type labeling6( const array3< T1, Allocator1 > &in, array3< T2, Allocator2 > &out, typename array3< T2, Allocator2 >::size_type max_label, Functor f )
00570 {
00571     typedef typename array3< T2, Allocator2 >::size_type  size_type;
00572     typedef typename array3< T2, Allocator2 >::value_type value_type;
00573 
00574     if( max_label == 0 )
00575     {
00576         if( is_float< value_type >::value )
00577         {
00578             max_label = type_limits< size_type >::maximum( );
00579         }
00580         else
00581         {
00582             max_label = static_cast< size_type >( type_limits< value_type >::maximum( ) );
00583         }
00584     }
00585 
00586     out.resize( in.size1( ), in.size2( ), in.size3( ) );
00587     out.reso1( in.reso1( ) );
00588     out.reso2( in.reso2( ) );
00589     out.reso3( in.reso3( ) );
00590 
00591     for( size_type i = 0 ; i < in.size( ) ; i++ )
00592     {
00593         out[ i ] = static_cast< value_type >( in[ i ] > 0 ? 1 : 0 );
00594     }
00595     return( __labeling_controller__::labeling( out, max_label, __labeling_controller__::neighbors< 6 >( ), f ) );
00596 }
00597 
00615 template < class T1, class T2, class Allocator1, class Allocator2 >
00616 inline typename array3< T2, Allocator2 >::size_type labeling6( const array3< T1, Allocator1 > &in, array3< T2, Allocator2 > &out, typename array3< T2, Allocator2 >::size_type max_label = __labeling_controller__::default_label_num3< T2 >::value )
00617 {
00618     return( labeling6( in, out, max_label, __mist_dmy_callback__( ) ) );
00619 }
00620 
00621 
00640 template < class T1, class T2, class Allocator1, class Allocator2, class Functor >
00641 typename array3< T2, Allocator2 >::size_type labeling18( const array3< T1, Allocator1 > &in, array3< T2, Allocator2 > &out, typename array3< T2, Allocator2 >::size_type max_label, Functor f )
00642 {
00643     typedef typename array3< T2, Allocator2 >::size_type  size_type;
00644     typedef typename array3< T2, Allocator2 >::value_type value_type;
00645 
00646     if( max_label == 0 )
00647     {
00648         if( is_float< value_type >::value )
00649         {
00650             max_label = type_limits< size_type >::maximum( );
00651         }
00652         else
00653         {
00654             max_label = static_cast< size_type >( type_limits< value_type >::maximum( ) );
00655         }
00656     }
00657 
00658     out.resize( in.size1( ), in.size2( ), in.size3( ) );
00659     out.reso1( in.reso1( ) );
00660     out.reso2( in.reso2( ) );
00661     out.reso3( in.reso3( ) );
00662 
00663     for( size_type i = 0 ; i < in.size( ) ; i++ )
00664     {
00665         out[ i ] = static_cast< value_type >( in[ i ] > 0 ? 1 : 0 );
00666     }
00667     return( __labeling_controller__::labeling( out, max_label, __labeling_controller__::neighbors< 18 >( ), f ) );
00668 }
00669 
00687 template < class T1, class T2, class Allocator1, class Allocator2 >
00688 inline typename array3< T2, Allocator2 >::size_type labeling18( const array3< T1, Allocator1 > &in, array3< T2, Allocator2 > &out, typename array3< T2, Allocator2 >::size_type max_label = __labeling_controller__::default_label_num3< T2 >::value )
00689 {
00690     return( labeling18( in, out, max_label, __mist_dmy_callback__( ) ) );
00691 }
00692 
00693 
00712 template < class T1, class T2, class Allocator1, class Allocator2, class Functor >
00713 typename array3< T2, Allocator2 >::size_type labeling26( const array3< T1, Allocator1 > &in, array3< T2, Allocator2 > &out, typename array3< T2, Allocator2 >::size_type max_label, Functor f )
00714 {
00715     typedef typename array3< T2, Allocator2 >::size_type  size_type;
00716     typedef typename array3< T2, Allocator2 >::value_type value_type;
00717 
00718     if( max_label == 0 )
00719     {
00720         if( is_float< value_type >::value )
00721         {
00722             max_label = type_limits< size_type >::maximum( );
00723         }
00724         else
00725         {
00726             max_label = static_cast< size_type >( type_limits< value_type >::maximum( ) );
00727         }
00728     }
00729 
00730     out.resize( in.size1( ), in.size2( ), in.size3( ) );
00731     out.reso1( in.reso1( ) );
00732     out.reso2( in.reso2( ) );
00733     out.reso3( in.reso3( ) );
00734 
00735     for( size_type i = 0 ; i < in.size( ) ; i++ )
00736     {
00737         out[ i ] = static_cast< value_type >( in[ i ] > 0 ? 1 : 0 );
00738     }
00739     return( __labeling_controller__::labeling( out, max_label, __labeling_controller__::neighbors< 26 >( ), f ) );
00740 }
00741 
00742 
00758 template < class T1, class T2, class Allocator1, class Allocator2 >
00759 inline typename array3< T2, Allocator2 >::size_type labeling26( const array3< T1, Allocator1 > &in, array3< T2, Allocator2 > &out, typename array3< T2, Allocator2 >::size_type max_label = __labeling_controller__::default_label_num3< T2 >::value )
00760 {
00761     return( labeling26( in, out, max_label, __mist_dmy_callback__( ) ) );
00762 }
00763 
00764 
00765 
00766 
00781 template < class T1,  class T2, class Allocator1, class Allocator2 >
00782 void maximum_region(
00783                         const array2< T1, Allocator1 > &in,
00784                         array2< T2, Allocator2 > &out,
00785                         typename array2< T1, Allocator1 >::size_type sx,
00786                         typename array2< T1, Allocator1 >::size_type ex,
00787                         typename array2< T1, Allocator1 >::size_type sy,
00788                         typename array2< T1, Allocator1 >::size_type ey,
00789                         typename array2< T1, Allocator1 >::size_type max_label = __labeling_controller__::default_label_num2< T2 >::value
00790                     )
00791 {
00792     typedef typename array2< T1, Allocator1 >::size_type size_type;
00793     typedef typename array2< T1, Allocator1 >::difference_type difference_type;
00794 
00795     array2< size_type > tmp;
00796     size_type i, j;
00797 
00798     size_type label_num = mist::labeling8( in, tmp, max_label );
00799 
00800     // 指定された範囲内の最大ラベルを探索
00801     sx = sx < 0 ? 0 : sx;
00802     sy = sy < 0 ? 0 : sy;
00803     sx = sx < in.width( )  ? sx : in.width( )  - 1;
00804     sy = sy < in.height( ) ? sy : in.height( ) - 1;
00805 
00806     ex = ex < 0 ? 0 : ex;
00807     ey = ey < 0 ? 0 : ey;
00808     ex = ex < in.width( )  ? ex : in.width( )  - 1;
00809     ey = ey < in.height( ) ? ey : in.height( ) - 1;
00810 
00811     size_type *menseki = new size_type[ label_num + 1 ];
00812     for( i = 0 ; i <= label_num ; i++ )
00813     {
00814         menseki[ i ] = 0;
00815     }
00816 
00817     for( j = sy ; j <= ey ; j++ )
00818     {
00819         for( i = sx ; i <= ex ; i++ )
00820         {
00821             menseki[ tmp( i, j ) ]++;
00822         }
00823     }
00824 
00825     max_label = 1;
00826     for( i = 2 ; i <= label_num ; i++ )
00827     {
00828         max_label = menseki[ i ] > menseki[ max_label ] ? i : max_label;
00829     }
00830     delete [] menseki;
00831 
00832     out.resize( in.size1( ), in.size2( ) );
00833     out.reso1( in.reso1( ) );
00834     out.reso2( in.reso2( ) );
00835 
00836     for( i = 0 ; i < out.size( ) ; i++ )
00837     {
00838         out[ i ] = tmp[ i ] == max_label ? 1 : 0;
00839     }
00840 }
00841 
00842 
00855 template < class T1,  class T2, class Allocator1, class Allocator2 >
00856 void maximum_region( const array2< T1, Allocator1 > &in, array2< T2, Allocator2 > &out, typename array2< T1, Allocator1 >::size_type max_label = __labeling_controller__::default_label_num2< T2 >::value )
00857 {
00858     maximum_region( in, out, 0, in.width( ) - 1, 0, in.height( ) - 1, max_label );
00859 }
00860 
00861 
00862 
00881 template < class T1,  class T2, class Allocator1, class Allocator2 >
00882 void maximum_region(
00883                         const array3< T1, Allocator1 > &in,
00884                         array3< T2, Allocator2 > &out,
00885                         typename array3< T1, Allocator1 >::size_type sx,
00886                         typename array3< T1, Allocator1 >::size_type ex,
00887                         typename array3< T1, Allocator1 >::size_type sy,
00888                         typename array3< T1, Allocator1 >::size_type ey,
00889                         typename array3< T1, Allocator1 >::size_type sz,
00890                         typename array3< T1, Allocator1 >::size_type ez,
00891                         typename array3< T1, Allocator1 >::size_type max_label = __labeling_controller__::default_label_num3< T2 >::value
00892                     )
00893 {
00894     typedef typename array3< T1, Allocator1 >::size_type size_type;
00895     typedef typename array3< T1, Allocator1 >::difference_type difference_type;
00896 
00897     array3< size_type > tmp;
00898     size_type i, j, k;
00899 
00900     size_type label_num = mist::labeling26( in, tmp, max_label );
00901 
00902     // 指定された範囲内の最大ラベルを探索
00903     sx = sx < 0 ? 0 : sx;
00904     sy = sy < 0 ? 0 : sy;
00905     sz = sz < 0 ? 0 : sz;
00906     sx = sx < in.width( )  ? sx : in.width( )  - 1;
00907     sy = sy < in.height( ) ? sy : in.height( ) - 1;
00908     sz = sz < in.depth( )  ? sz : in.depth( )  - 1;
00909 
00910     ex = ex < 0 ? 0 : ex;
00911     ey = ey < 0 ? 0 : ey;
00912     ez = ez < 0 ? 0 : ez;
00913     ex = ex < in.width( )  ? ex : in.width( )  - 1;
00914     ey = ey < in.height( ) ? ey : in.height( ) - 1;
00915     ez = ez < in.depth( )  ? ez : in.depth( )  - 1;
00916 
00917     size_type *menseki = new size_type[ label_num + 1 ];
00918     for( i = 0 ; i <= label_num ; i++ )
00919     {
00920         menseki[ i ] = 0;
00921     }
00922 
00923     for( k = sz ; k <= ez ; k++ )
00924     {
00925         for( j = sy ; j <= ey ; j++ )
00926         {
00927             for( i = sx ; i <= ex ; i++ )
00928             {
00929                 menseki[ tmp( i, j, k ) ]++;
00930             }
00931         }
00932     }
00933 
00934     max_label = 1;
00935     for( i = 2 ; i <= label_num ; i++ )
00936     {
00937         max_label = menseki[ i ] > menseki[ max_label ] ? i : max_label;
00938     }
00939     delete [] menseki;
00940 
00941     out.resize( in.size1( ), in.size2( ), in.size3( ) );
00942     out.reso1( in.reso1( ) );
00943     out.reso2( in.reso2( ) );
00944     out.reso3( in.reso3( ) );
00945 
00946     for( i = 0 ; i < out.size( ) ; i++ )
00947     {
00948         out[ i ] = static_cast< typename array3< T2, Allocator2 >::value_type >( tmp[ i ] == max_label ? 1 : 0 );
00949     }
00950 }
00951 
00952 
00965 template < class T1,  class T2, class Allocator1, class Allocator2 >
00966 void maximum_region( const array3< T1, Allocator1 > &in, array3< T2, Allocator2 > &out, typename array3< T1, Allocator1 >::size_type max_label = __labeling_controller__::default_label_num3< T2 >::value )
00967 {
00968     maximum_region( in, out, 0, in.width( ) - 1, 0, in.height( ) - 1, 0, in.depth( ) - 1, max_label );
00969 }
00970 
00971 
00972 
00973 
00985 template < class T1,  class T2, class Allocator1, class Allocator2 >
00986 void remove_hole_region( const array2< T1, Allocator1 > &in, array2< T2, Allocator2 > &out, const bool include_corner_labels, typename array2< T1, Allocator1 >::size_type max_label = __labeling_controller__::default_label_num2< T2 >::value )
00987 {
00988     typedef typename array2< T1, Allocator1 >::size_type size_type;
00989     typedef typename array2< T1, Allocator1 >::difference_type difference_type;
00990 
00991     array2< size_type > tmp;
00992     size_type i;
00993 
00994     tmp.resize( in.size1( ), in.size2( ) );
00995     tmp.reso1( in.reso1( ) );
00996     tmp.reso2( in.reso2( ) );
00997 
00998     // 反転した画像を作成する
00999     for( i = 0 ; i < tmp.size( ) ; i++ )
01000     {
01001         tmp[ i ] = in[ i ] == 0;
01002     }
01003 
01004     size_type label_num = mist::labeling4( tmp, tmp, max_label );
01005 
01006     if ( include_corner_labels )
01007     {
01008         size_type *L = new size_type[ label_num + 1 ];
01009 
01010         for( size_type i = 0 ; i <= label_num ; i++ )
01011         {
01012             L[ i ] = static_cast< size_type >( i );
01013         }
01014 
01015         L[ tmp( 0, 0 ) ] = 1;
01016         L[ tmp( tmp.width() - 1, 0 ) ] = 1;
01017         L[ tmp( 0, tmp.height() - 1 ) ] = 1;
01018         L[ tmp( tmp.width() - 1, tmp.height() - 1 ) ] = 1;
01019         
01020         for( size_type i = 0 ; i < tmp.size( ) ; i++ )
01021         {
01022             tmp[ i ] = L[ tmp[ i ] ];
01023         }
01024 
01025         delete [] L;
01026     }
01027 
01028     // 指定された範囲内の最大ラベルを探索
01029     size_type *menseki = new size_type[ label_num + 1 ];
01030     for( i = 0 ; i <= label_num ; i++ )
01031     {
01032         menseki[ i ] = 0;
01033     }
01034 
01035     for( i = 0 ; i < tmp.size( ) ; i++ )
01036     {
01037         menseki[ tmp[ i ] ]++;
01038     }
01039 
01040     max_label = 1;
01041     for( i = 2 ; i <= label_num ; i++ )
01042     {
01043         max_label = menseki[ i ] > menseki[ max_label ] ? i : max_label;
01044     }
01045     delete [] menseki;
01046 
01047     out.resize( in.size1( ), in.size2( ) );
01048     out.reso1( in.reso1( ) );
01049     out.reso2( in.reso2( ) );
01050 
01051     // 最大成分を残し，反転した画像を出力する
01052     for( i = 0 ; i < out.size( ) ; i++ )
01053     {
01054         out[ i ] = tmp[ i ] == max_label ? 0 : 1;
01055     }
01056 }
01057 
01058 
01069 template < class T1,  class T2, class Allocator1, class Allocator2 >
01070 void remove_hole_region( const array2< T1, Allocator1 > &in, array2< T2, Allocator2 > &out, typename array2< T1, Allocator1 >::size_type max_label = __labeling_controller__::default_label_num2< T2 >::value )
01071 {
01072     remove_hole_region( in, out, false, max_label );
01073 }
01074 
01075 
01087 template < class T1,  class T2, class Allocator1, class Allocator2 >
01088 void remove_hole_region( const array3< T1, Allocator1 > &in, array3< T2, Allocator2 > &out, const bool include_corner_labels, typename array3< T1, Allocator1 >::size_type max_label = __labeling_controller__::default_label_num3< T2 >::value )
01089 {
01090     typedef typename array2< T1, Allocator1 >::size_type size_type;
01091     typedef typename array2< T1, Allocator1 >::difference_type difference_type;
01092 
01093     array3< size_type > tmp;
01094     size_type i;
01095 
01096     tmp.resize( in.size1( ), in.size2( ), in.size3( ) );
01097     tmp.reso1( in.reso1( ) );
01098     tmp.reso2( in.reso2( ) );
01099     tmp.reso3( in.reso3( ) );
01100 
01101     // 反転した画像を作成する
01102     for( i = 0 ; i < tmp.size( ) ; i++ )
01103     {
01104         tmp[ i ] = in[ i ] == 0;
01105     }
01106 
01107     size_type label_num = mist::labeling6( tmp, tmp, max_label );
01108 
01109     if ( include_corner_labels )
01110     {
01111         size_type *L = new size_type[ label_num + 1 ];
01112 
01113         for( size_type i = 0 ; i <= label_num ; i++ )
01114         {
01115             L[ i ] = static_cast< size_type >( i );
01116         }
01117 
01118         L[ tmp( 0, 0, 0 ) ] = 1;
01119         L[ tmp( tmp.width() - 1, 0, 0 ) ] = 1;
01120         L[ tmp( 0, tmp.height() - 1, 0 ) ] = 1;
01121         L[ tmp( 0, 0, tmp.depth() - 1 ) ] = 1;
01122         L[ tmp( tmp.width() - 1, tmp.height() - 1, 0 ) ] = 1;
01123         L[ tmp( 0, tmp.height() - 1, tmp.depth() - 1 ) ] = 1;
01124         L[ tmp( tmp.width() - 1, 0, tmp.depth() - 1 ) ] = 1;
01125         L[ tmp( tmp.width() - 1, tmp.height() - 1, tmp.depth() - 1 ) ] = 1;
01126         
01127         for( size_type i = 0 ; i < tmp.size( ) ; i++ )
01128         {
01129             tmp[ i ] = L[ tmp[ i ] ];
01130         }
01131 
01132         delete [] L;
01133     }
01134 
01135     // 指定された範囲内の最大ラベルを探索
01136     size_type *menseki = new size_type[ label_num + 1 ];
01137     for( i = 0 ; i <= label_num ; i++ )
01138     {
01139         menseki[ i ] = 0;
01140     }
01141 
01142     for( i = 0 ; i < tmp.size( ) ; i++ )
01143     {
01144         menseki[ tmp[ i ] ]++;
01145     }
01146 
01147     max_label = 1;
01148     for( i = 2 ; i <= label_num ; i++ )
01149     {
01150         max_label = menseki[ i ] > menseki[ max_label ] ? i : max_label;
01151     }
01152     delete [] menseki;
01153 
01154     out.resize( in.size1( ), in.size2( ), in.size3( ) );
01155     out.reso1( in.reso1( ) );
01156     out.reso2( in.reso2( ) );
01157     out.reso3( in.reso3( ) );
01158 
01159     // 最大成分を残し，反転した画像を出力する
01160     for( i = 0 ; i < out.size( ) ; i++ )
01161     {
01162         out[ i ] = tmp[ i ] == max_label ? 0 : 1;
01163     }
01164 }
01165 
01176 template < class T1,  class T2, class Allocator1, class Allocator2 >
01177 void remove_hole_region( const array3< T1, Allocator1 > &in, array3< T2, Allocator2 > &out, typename array3< T1, Allocator1 >::size_type max_label = __labeling_controller__::default_label_num3< T2 >::value )
01178 {
01179     remove_hole_region( in, out, false, max_label );
01180 }
01181 
01182 
01183 namespace __he__
01184 {
01185     template< class L >
01186     struct table_type
01187     {
01188         typedef typename array< L >::value_type     label_type;
01189         label_type label;
01190         table_type *next;
01191         table_type *tail;
01192         table_type( ) : label( 0 ), next( NULL ), tail( NULL )
01193         {
01194         }
01195     };
01196 
01197     template< class L, class Allocator >
01198     inline void resolve( const typename array< L, Allocator >::value_type::label_type u, const typename array< L, Allocator >::value_type::label_type v, array< table_type< L >, Allocator > &table )
01199     {
01200         typedef typename array< L, Allocator >::value_type  table_type;
01201         typedef typename table_type::label_type             label_type;
01202         if( table[ u ].label != table[ v ].label )
01203         {
01204             table_type *pu;
01205             table_type *pv;
01206             if( table[ u ].label < table[ v ].label )
01207             {
01208                 pu = &table[ table[ u ].label ];
01209                 pv = &table[ table[ v ].label ];
01210             }
01211             else
01212             {
01213                 pu = &table[ table[ v ].label ];
01214                 pv = &table[ table[ u ].label ];
01215             }
01216             pu->tail->next = pv;
01217             pu->tail = pv->tail;
01218             while( pv )
01219             {
01220                 pv->label = pu->label;
01221                 pv = pv->next;
01222             }
01223         }
01224     }
01225 
01226     template< class L, class Allocator >
01227     inline void update( typename array< L, Allocator >::value_type::label_type &m, array< table_type< L >, Allocator > &table )
01228     {
01229         table[ m ].label = m;
01230         table[ m ].tail  = &table[ m ];
01231         m++;
01232     }
01233 }
01234 
01235 
01236 namespace he
01237 {
01254     template< typename T1, class Allocator1, typename T2, class Allocator2 >
01255     inline typename array2< T2, Allocator2 >::size_type labeling8( const array2< T1, Allocator1 > &b, array2< T2, Allocator2 > &v )
01256     {
01257         typedef typename array2< T1, Allocator1 >::size_type        size_type;
01258         typedef typename array2< T1, Allocator1 >::difference_type  difference_type;
01259         typedef typename array2< T1, Allocator1 >::value_type       value_type;
01260         typedef typename array2< T2, Allocator2 >::value_type       label_type;
01261         typedef typename array2< T1, Allocator1 >::const_pointer    ipointer;
01262         typedef typename array2< T2, Allocator2 >::pointer          opointer;
01263 
01264         typedef typename __he__::table_type< label_type >           table_type;
01265 
01266         const size_type size = ( ( b.width( ) + 1 ) / 2 ) * ( ( b.height( ) + 1 ) / 2 ); 
01267         array< table_type > table( size );
01268         label_type m = 1;
01269 
01270         v.resize( b.width( ), b.height( ) );
01271 
01272         ipointer ip  = &b( 0, 0 );
01273         opointer op1 = &v( 0, 0 );
01274 
01275         if( ip[ 0 ] != 0 )
01276         {
01277             op1[ 0 ] = m;
01278             __he__::update( m, table );
01279         }
01280 
01281         for( size_type i = 1 ; i < b.width( ) ; i++ )
01282         {
01283             if( ip[ i ] != 0 )
01284             {
01285                 if( op1[ i - 1 ] != 0 )
01286                 {
01287                     op1[ i ] = op1[ i - 1 ];
01288                 }
01289                 else
01290                 {
01291                     op1[ i ] = m;
01292                     __he__::update( m, table );
01293                 }               
01294             }
01295         }
01296 
01297         // 一つ前のラインを覚える
01298         opointer op0 = op1;
01299 
01300         // 1ライン下に進める
01301         ip  += b.width( );
01302         op1 += v.width( );
01303 
01304         for( size_type j = 1 ; j < b.height( ) ; j++ )
01305         {
01306             if( ip[ 0 ] != 0 )
01307             {
01308                 if( op0[ 0 ] != 0 )
01309                 {
01310                     op1[ 0 ] = op0[ 0 ];
01311                 }
01312                 else if( op0[ 1 ] != 0 )
01313                 {
01314                     op1[ 0 ] = op0[ 1 ];
01315                 }
01316                 else
01317                 {
01318                     op1[ 0 ] = m;
01319                     __he__::update( m, table );
01320                 }               
01321             }
01322 
01323             size_type i = 1;
01324             for( ; i < b.width( ) - 1 ; i++ )
01325             {
01326                 if( ip[ i ] != 0 )
01327                 {
01328                     if( op0[ i ] != 0 )
01329                     {
01330                         op1[ i ] = op0[ i ];
01331                     }
01332                     else if( op1[ i - 1 ] != 0 )
01333                     {
01334                         op1[ i ] = op1[ i - 1 ];
01335                         if( op0[ i + 1 ] != 0 )
01336                         {
01337                             __he__::resolve( op1[ i - 1 ], op0[ i + 1 ], table );
01338                         }
01339                     }
01340                     else if( op0[ i - 1 ] != 0 )
01341                     {
01342                         op1[ i ] = op0[ i - 1 ];
01343                         if( op0[ i + 1 ] != 0 )
01344                         {
01345                             __he__::resolve( op0[ i - 1 ], op0[ i + 1 ], table );
01346                         }
01347                     }
01348                     else if( op0[ i + 1 ] != 0 )
01349                     {
01350                         op1[ i ] = op0[ i + 1 ];
01351                     }
01352                     else
01353                     {
01354                         op1[ i ] = m;
01355                         __he__::update( m, table );
01356                     }
01357                 }
01358             }
01359 
01360             if( ip[ i ] != 0 )
01361             {
01362                 if( op0[ i ] != 0 )
01363                 {
01364                     op1[ i ] = op0[ i ];
01365                 }
01366                 else if( op1[ i - 1 ] != 0 )
01367                 {
01368                     op1[ i ] = op1[ i - 1 ];
01369                 }
01370                 else if( op0[ i - 1 ] != 0 )
01371                 {
01372                     op1[ i ] = op0[ i - 1 ];
01373                 }
01374                 else
01375                 {
01376                     op1[ i ] = m;
01377                     __he__::update( m, table );
01378                 }               
01379             }
01380 
01381             op0  = op1;
01382             ip  += b.width( );
01383             op1 += v.width( );
01384         }
01385 
01386         array< label_type > l_table( m );
01387         label_type l = 0;
01388         for( size_type i = 1 ; i < m ; i++ )
01389         {
01390             if( l_table[ table[ i ].label ] == 0 )
01391             {
01392                 l++;
01393                 l_table[ table[ i ].label ] = l;
01394             }
01395         }
01396 
01397         for( size_t i = 0 ; i < v.size( ) ; i++ )
01398         {
01399             v[ i ] = l_table[ table[ v[ i ] ].label ];
01400         }
01401 
01402         return( static_cast< size_type >( l ) );
01403     }
01404 }
01405 
01407 //  ラベリンググループの終わり
01408 
01409 
01410 // mist名前空間の終わり
01411 _MIST_END
01412 
01413 
01414 #endif // __INCLUDE_MIST_LABELING__
01415 
