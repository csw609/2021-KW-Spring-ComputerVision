//---------------------------------------------------------------------------
#ifndef kfcH
#define kfcH

////////////////////////////////////////////////////////////////////////////////////
//
// This library can be freely used and reproduced by anyone.
//
// KFC library by Jeong, Mun-Ho since 2004.05.01
// latest update : 2012.03.20
//
////////////////////////////////////////////////////////////////////////////////////

//sorting
#define _DESCEND    0
#define _ASCEND     1

//for matrix operations
#define _REPLACE     0
#define _ADD         1
#define _ZERO        0
#define _ONE		 1
#define _IDENTITY    2
#define _DIAGONAL    3

//position
#define _LEFT        0
#define _RIGHT       1
#define _UPP         2
#define _DOWN        3
#define _BACK		 4
#define _FRONT		 5
#define	_TOP		 6
#define _BOTTOM		 7

//rotation
#define	_CW			 0
#define	_CCW		 1

//for matrix, rect object
#define _ROW         0
#define _COL         1
#define _BOTH        2
#define _CENTER      3
#define _ORIGIN		 4

//degree and radian
#define _DEG         0
#define _RAD         1

//memory alloc. of array object
#define _ALLOC       0
#define _LOCK        1

//smoothing
#define _MEDIAN		 	0
#define _MEDIAN_RANK 	0
#define _MEDIAN_VALUE 	1
#define _GAUSSIAN    	2

//transformation
#define _RIGID              0
#define _SIMILARITY         1
#define _AFFINE             2
#define _PERSPECTIVE        3
#define _RECT_GENERIC       4
#define _ELLIPSE_GENERIC    5

//image format
#define _NRG         0
#define _YUV         1
#define _HSI         2
#define _RGB         3
#define _CS          4
#define _GRAY		 5
#define _RGB_ONEBYTE 6  //r:3bit | g:3bit | b:2bit
#define	_BINARY      7


//color
#define _RED         0
#define _GREEN       1
#define _BLUE        2

//axis
#define _X_AXIS     0
#define _Y_AXIS     1
#define _Z_AXIS     2

#define	_START		0
#define _END		1

#define _DEFAULT	0
#define _ABSOLUTE	1

//circle detection
#define		_OUTWARD_EDGE		0
#define		_OUTWARD			0
#define		_INWARD_EDGE		1
#define		_INWARD     		1
#define		_INOUTWARD_EDGE     2
#define		_OUT_SCAN			1
#define     _OUT_SCAN_MAX       2
#define		_OUT_SCAN_FULL     	3
#define		_IN_SCAN			4
#define     _IN_SCAN_MAX        5
#define		_IN_SCAN_FULL      	6
#define		_INOUT_SCAN     	0

//KRandom
#define		_RANDOM_IA		16807
#define		_RANDOM_IM		2147483647
#define		_RANDOM_AM		(1.0/_RANDOM_IM)
#define		_RANDOM_IQ		127773
#define		_RANDOM_IR		2836
#define		_RANDOM_NTAB	32
#define		_RANDOM_NDIV	(1+(_RANDOM_IM-1)/_RANDOM_NTAB)
#define     _RANDOM_EPS     1.2e-7
#define		_RANDOM_RNMX	(1.0-_RANDOM_EPS)



//vector normalization
#define _NO_NORMALIZE       0
#define _DTB_NORMALIZE      1 //mean 0 and std 1
#define _SIZE_NORMALIZE     2 //size 1
#define _HEQ_NORMALIZE      3 //histogram equalization
#define _MEAN_NORMALIZE     4 //mean 0
#define _STD_NORMALIZE      5 //std 1
#define _UNITSUM_NORMALIZE  6 //sum 1

//matrix
#define _NO_SCALING         0
#define _DEFAULT_SCALING    1
#define _USER_SCALING       2

#define _PI                                 3.1415926535897932385
#define _2PI                                6.283185307179586477
#define	_SQR(a)                             ((a)*(a))
#define	_MAX(a,b)                           (((a)>(b)) ? (a):(b))
#define	_MIN(a,b)                           (((a)<(b)) ? (a):(b))
#define _DIFF(a,b)                          ((a)>(b)   ? (a)-(b):(b)-(a))
#define _ABS(a)                             ((a)>0.0   ? (a):-(a))
#define	_SIGN(a)                            ((a)<0.0 ? -1 : 1)
#define	_SIGNEX(a,b)                        ((b)<0.0 ? -(a) : (a))
#define _DEGREE(a)                          ((a)*57.2957795130823)
#define _RADIAN(a)                          ((a)/57.2957795130823)
#define _INTENSITY(r,g,b)                   (0.299*(r) + 0.587*(g) + 0.114*(b))
#define _PARABOLICCENTER(x1,y1,x2,y2,x3,y3) (((x2)+(x3))*((y2)-(y1))-((x1)+(x2))*((y3)-(y2)))/(2*(2*(y2)-(y1)-(y3)))


/////for Atan()
#define _ATAN_CF0  (-15.8131890796f)
#define _ATAN_CF1  (61.0941945596f)
#define _ATAN_CF2  (-0.140500406322f)

//
#define		_BACKGROUND		0
#define		_FOREGROUND		1

//배수
#define     _SINGLE         1
#define     _DOUBLE         2
#define     _TRIPLE         3
#define     _QUADRUPLE      4
#define     _MULTI          5


////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <assert.h>
#include <memory.h>
#include <string.h>
#include <math.h>
#include <sys/timeb.h>

////////////////////////////////////////////////////////////////////////////////////

typedef struct tagKHSI
{
	float i;
	float s;
	float h;
}KHSI;


typedef struct tagKHSV
{
	double v;
	double s;
	double h;
}KHSV;


typedef struct tagKTRIPLET
{
	double r;
	double g;
	double b;
}KTRIPLET;


typedef struct tagKTRIPLETF
{
	float r;
	float g;
	float b;
}KTRIPLETF;

typedef struct tagKYUV
{
	unsigned char y;
	unsigned char u;
	unsigned char v;
}KYUV;

struct KIRG
{
	unsigned char i;
	float         r;
	float         g;
};

struct KCOLOR32
{
	unsigned char b;//or V
	unsigned char g;//or U
	unsigned char r;//or Y
	unsigned char dummy;

    KCOLOR32( ) {   }
    KCOLOR32(const unsigned char& rr, const unsigned char& gg,const unsigned char& bb) : r(rr),g(gg),b(bb) {   }
};

struct KCOLOR24{
	unsigned char b;
	unsigned char g;
	unsigned char r;
};



struct KPOINT
{
	int nX;
	int nY;

    KPOINT(){ }
    KPOINT(const int& nXo, const int& nYo) : nX(nXo), nY(nYo){ }    
} ;

struct KPOINT3
{
    int nX;
    int nY;
    int nZ;

    KPOINT3() { }
    KPOINT3(const int& nXo, const int& nYo, const int& nZo) : nX(nXo), nY(nYo), nZ(nZo){  }
} ;


typedef struct tagKPOINTW
{
	unsigned short wX;
	unsigned short wY;
} KPOINTW;

struct KPOINTD
{
	double dX;
	double dY;

    KPOINTD() { }
    KPOINTD(const double& dXo, const double& dYo) : dX(dXo), dY(dYo){  }
};


typedef struct tagKPOINTF
{
	float fX;
	float fY;
} KPOINTF;


typedef struct tagKPOINT3W

{
	unsigned short wX;
	unsigned short wY;
	unsigned short wZ;
} KPOINT3W;


struct KPOINT3D
{
	double dX;
	double dY;
	double dZ;

    KPOINT3D() { }
    KPOINT3D(const double& dXo, const double& dYo, const double& dZo) : dX(dXo), dY(dYo), dZ(dZo){  }
};


typedef struct tagKPOINT3F
{
	float fX;
	float fY;
	float fZ;
} KPOINT3F;


typedef union tagKTRIANGLEF

{
	KPOINT3F	ptpTri[3];
	float		fpTri[9];
	
} KTRIANGLEF;



typedef struct tagKPIXEL

{
	unsigned short	u;
	unsigned short	v;
	unsigned short 	i;
	unsigned short  id;
} KPIXEL;


typedef struct tagKPIXEL24

{
	int 			u;
	int 			v;
	unsigned char 	b;
	unsigned char 	g;
	unsigned char 	r;

} KPIXEL24;

typedef struct tagKMONOCAM_PARAM
{
    double     fu;              //  |  fu  gamma    uo |
    double     fv;              //  |  0     fv     vo |
	double		gamma;           //  |  0     0      1  | 
	double		uo;
	double		vo;
	double		k1,k2,k3,k4;     // k1,k2: radial distortion;  k3,k4: tangential distortion
    int			    width,height;    //image size
	
} KMONOCAM_PARAM;

typedef struct tagKSTEREOCAM_PARAM        
{
	KMONOCAM_PARAM	oCam1;
	KMONOCAM_PARAM	oCam2;

    double		r[9];        // Xcam2 = r * Xcam1 + t
    double		t[3];
	
} KSTEREOCAM_PARAM;


class KObject

{
public:
	KObject(){};
	virtual ~KObject(){};

    virtual void    Init(void* pInfo) = 0;
    virtual void*   Run(void* p1,void* p2,void* p3,void* p4,void* p5) = 0;

    virtual void*   Info() = 0;
};


///////////////////
// functions of "Numerical Recipes in C"
//
/*
double Pythag(double a, double b)
{
	double absa,absb;
	absa=fabs(a);
	absb=fabs(b);
	if (absa > absb) return absa*sqrt(1.0+_SQR(absb/absa));
	else return (absb == 0.0 ? 0.0 : absb*sqrt(1.0+_SQR(absa/absb)));
}
*/
////////////////////

//
////////////////////////////////////////////////////////////
//
// class KArray

//

//class KRect;


template< class T > class KArray //tag : ar

{
	unsigned int	_nRow;
	unsigned int	_nCol;
	unsigned int   	_nSize;
	int     		_nMode;

public:
	T**		_ppA;
	char    _szNote[100];

public:
	KArray();
	KArray(const KArray<T>& arFrom){ _ppA=0; Create(arFrom._nRow,arFrom._nCol,arFrom._ppA[0]); }
	KArray(const int& nRow, const int& nCol);
	KArray(const int& nRow, const int& nCol,T* p,int nMode=_ALLOC);
	virtual ~KArray();

	void   Create(const int& nRow, const int& nCol);
	void   Create(const int& nRow, const int& nCol,T* p,int nMode=_ALLOC);

    void   Release();
    void   Clear(){ if(_ppA) memset(_ppA[0],0,sizeof(T)*Size()); }
    T*     Address() const { return (_ppA ? _ppA[0]:0); }
    T*	   Pointer() const { return (_ppA ? _ppA[0]:0); }
	T**    PPointer() const { return _ppA; }

public:
	unsigned int   	Col()  const { return _nCol; }
	unsigned int   	Row()  const { return _nRow; }
	unsigned int 	Size() const { return (_ppA ? _nSize:0); }
//	KRect		  	Rect() const { return KRect(0,0,_nCol-1,_nRow-1); }
	void			Fliped();

	T*			  operator [] ( const int& i ) const;
	KArray<T>&	  operator =  ( const T& 	t);
	KArray<T>&	  operator =  ( const KArray<T>& a);
};


typedef KArray<float>           KArrayFloat;    //tag: af
typedef KArray<char>            KArrayChar;     //tag: ac
typedef KArray<unsigned int>    KArrayDWord;    //tag: ad

//
////////////////////////////////////////////////////////////
//
// class KArrayObject

//

template< class T > class KArrayObject //tag : ar

{
	int				_nRow;
	int    			_nCol;
	unsigned int   	_nSize;

public:
	T**		_ppA;
	char    _szNote[100];

public:
	KArrayObject(){ _ppA = 0; }
	KArrayObject(const KArrayObject<T>& arFrom){ _ppA=0; Create(arFrom); }
	KArrayObject(const int& nRow, const int& nCol){ _ppA=0; Create(nRow,nCol); }

	void   	Create(const int& nRow, const int& nCol);
	void    Create(const KArrayObject<T>& arFrom);

    void    Release( );
    T*      Address( ) const { return (_ppA ? _ppA[0]:0); }
    T*      Pointer( ) const { return (_ppA ? _ppA[0]:0); }
    T**     PPointer() const { return _ppA; }

public:
    int             Col()  const { return _nCol; }
	int            	Row()  const { return _nRow; }
	unsigned int 	Size() const { return (_ppA ? _nSize:0); }

    T*			  		operator [] ( const int& i ) const;
    KArrayObject<T>&    operator =  ( const KArrayObject<T>& a);
};


////////////////////////////////////////////////////////////
//
// class KList

template< class T > class KList //tag : l
{
	unsigned int    _uiCapacity;
	unsigned int    _uiCount;
    T*              _pItems;

public:
	KList(const unsigned int& uiCapacity = 500);
    virtual ~KList() { RemoveAll(); if(_pItems) delete[] _pItems; }

    void                Create(const unsigned int& uiCapacity);
    void                RemoveAll();
    unsigned int        RemoveAt(const unsigned int&);
    unsigned int        Add(T);
    unsigned int        Add(KList<T>& lAdd);
    unsigned int        Find(const T&);
    unsigned int        Count()    const{ return _uiCount; }
    unsigned int        Capacity() const{ return _uiCapacity; }
    bool                IsEmpty(){ return !(_uiCount ? true : false); }
    bool                Enable(){  return (bool)(_pItems); }

    KList<T>&           Reversed( );
    T&                  First(){ return _pItems[0]; }
    T&                  Last(){
#ifdef _DEBUG
                                    assert(_uiCount);
#endif
                                    return _pItems[_uiCount-1];
                                }
    void                     Swap(const unsigned int&,const unsigned int&);
    T&                       Item(const unsigned int& uiID){ return _pItems[uiID]; }

	//operators
	T&	        operator [] ( const unsigned int& uiID)
	{
#ifdef _DEBUG
				assert(_uiCount > uiID);
#endif
				return _pItems[uiID];
	}
	T	        operator [] ( const unsigned int& uiID) const
	{
#ifdef _DEBUG
				assert(_uiCount > uiID);
#endif
				return _pItems[uiID];
	}

	KList<T>&   operator =  ( const KList<T>& o);
};

class KPoint;

template< class T >
class KPtrList //tag : pl
{
protected:
    char            _szID[30];
    unsigned int   	_uiCapacity;
    int    			_uiCount;
    T*     			_pItems;
    bool   			_bOwnership;
    bool   			_bArray;

public:
	KPtrList(const unsigned int& uiCapacity=1000,bool bOwnership=true,bool bArray=false);
	virtual ~KPtrList(){ RemoveAll(); if(_pItems) delete[] _pItems; }

	void   		 Create(const unsigned int& nCapacity,bool bOwnership=true,bool bArray=false);
	void   		 RemoveAll();
    void   		 RemoveAt(const unsigned int&);
	void   		 Remove(const T&);
	void   		 Remove(const unsigned int& nFrom,const unsigned int& nTo);
	unsigned int Add(T);
	unsigned int Add(KPtrList<T>* lpList);

    unsigned int    Count()    const{ return _uiCount; }
    unsigned int    Capacity() const{ return _uiCapacity; }
    bool&           Ownership(){ return _bOwnership; }
    bool   		    IsEmpty(){ return !(_uiCount ? true : false); }


    T               First(){ return _pItems[0]; }
    T               Last(){  return (_uiCount ? _pItems[_uiCount-1]:0); }
    void            Swap(const unsigned int&,const unsigned int&);
    int             Find(const T&);
    T               Item(const unsigned int& uiID){ return _pItems[uiID]; }
    char*           ID(){ return _szID; }

	//operators
    T               operator [] ( const unsigned int& uiID) const { return _pItems[uiID]; }
    T&              operator [] ( const unsigned int& uiID){        return _pItems[uiID]; }
    KPtrList<T>&    operator =  ( KPtrList<T>& plList);
};

typedef KPtrList<KPoint*> 	  KBlob;
typedef KPtrList<KBlob*>    KBlobList;
typedef KPtrList<KPOINT*>  KBlobN;
typedef KPtrList<KBlobN*>    KBlobNList;
typedef KPtrList<KPIXEL*> KListPixel;


////////////////////////////////////////////////////////////
//
// class KStack


template< class T > class KStack  //tag : sk
{
protected:
    T*      _pStack;
    int     _nCapacity;
    int     _nCount;
    int     _nCur;
    bool    _bLock;

public:	
    KStack(const int& nCapacity = 2000){ _pStack=0; _nCount=_nCur=0; _bLock=false; Create(nCapacity); }
	virtual ~KStack();

    void         Create(const int& nCapacity);
    void         Lock(){   _bLock = true; }
    void         UnLock(){ _bLock = false; _nCur = _nCount; }
    void         RemoveAll();
    void         RemoveAt(const int& idx);
    void         Push(const T&);
    int          Pop(T&);
    int          Count(){ return _nCount; }
    int          Capacity(){ return _nCapacity; }
    virtual void Sort(const int& nType){ };

	T            operator [](const int& nID);
};

////////////////////////////////////////////////////////////
//
// class KQueue

template< class T > class KQueue  //tag : q
{
protected:
    T*      _pQueue;
    int     _nCapacity;
    int     _nIn;
    int     _nOut;
    int     _nRef;
    int		_nCount;

public:
    KQueue(){ _pQueue = 0; }
    KQueue(const int& nCapacity){ _pQueue = 0; Create(nCapacity); }
    virtual ~KQueue(){ if(_pQueue) delete[] _pQueue; }

    void    Create(const int& nCapacity);
    void    RemoveAll();
    int     Remove(const T& oDel);
    int     Push(const T& in, int* npIdx=0, T* pRemoved=0);
    int     Pop(T& out);
    bool    Peek(T& out);
    bool    Peek(int k,T& out);
    T&      Peek(int k);
    int     FirstIdx(){ return _nOut; }
    T&      First(){ return _pQueue[_nOut]; }
    int     LastIdx(){ return (_nIn ? _nIn-1 : _nCapacity-1); }
    T&      Last(){  return _pQueue[ (_nIn ? _nIn-1 : _nCapacity-1) ]; }
    int     Count(){ return _nCount; }
    int     Capacity(){ return _nCapacity; }
    bool    IsFull(){ return (_nCount == _nCapacity); }
	void	Reverse();
    void    Swap(const int& n1,const int& n2);

    virtual void Sort(const int& nType){  };

    T       operator [] ( const int& nID) const { return _pQueue[nID]; }
    T&      operator [] ( const int& nID){        return _pQueue[nID]; }

};


template< class T > class KPtrQueue  //tag : q
{
protected:
    T*      _pQueue;
    int     _nCapacity;
    int     _nIn;
    int     _nOut;
    int		_nRef;
    int		_nCount;
	bool   	_bOwnership;
    bool    _bFixedCapacity; //whether the size of capacity is fixed

public:
    KPtrQueue( ){ _pQueue = 0;   }
    KPtrQueue(const int& nCapacity, bool bOwnership = true, bool bFixedCapacity = true){ _pQueue = 0;  Create(nCapacity,bOwnership, bFixedCapacity); }
    virtual ~KPtrQueue(){ RemoveAll();  if(_pQueue) delete[] _pQueue; }

    void        Create(const int& nCapacity, bool bOwnership=true, bool bFixedCapacity = true);
    void        RemoveAll();
    int         Remove(const T& out);
    int         Push(const T& in, int* npIdx=0);
    int         Pop(T& out);
    bool        Peek(T& out);
    void        PeekReset() { _nRef = 0; }
    bool        Peek(int k,T& out); // 0 <= k < _nCapacity
    int         FirstIdx(){ return _nOut; }
    int         Count(){ return _nCount; }
    int         Capacity(){ return _nCapacity; }
    void        Swap(const int& n1,const int& n2);

    virtual void Sort(const int& nType){  };

};

//
////////////////////////////////////////////////////////////
//
//class KPoint
class KVector;
class KPoints;

class KPoint //tag : pt
{
public:
	double _dX;
	double _dY;

	KPoint(){  };
	KPoint(const KPoint& pt){ _dX=pt._dX; _dY=pt._dY; }
    KPoint(const KPOINTD& pt){ _dX=pt.dX; _dY=pt.dY; }
    KPoint(const KPOINT& pt){ _dX=pt.nX; _dY=pt.nY; }
	KPoint(const double& x, const double&y){ _dX=x; _dY=y; }
	virtual ~KPoint(){ }

public:
	bool        Read(FILE* fp);
	void        Write(FILE* fp);
	double      Distance(const KPoint& pt){ return sqrt(_SQR(pt._dX-_dX)+_SQR(pt._dY-_dY)); }
	double      Distance2(const KPoint& pt){ return (_SQR(pt._dX-_dX)+_SQR(pt._dY-_dY)); }
	double      Distance(const int& x,const int& y){ return sqrt(_SQR(_dX-x)+_SQR(_dY-y)); }
	double      Distance2(const int& x,const int& y){ return (_SQR(_dX-x)+_SQR(_dY-y)); }
	void        Rotated(const double& dRad,const double& dXo=0.0, const double& dYo=0.0);
	void        Rotated(const double& dRad,const KPoint& pt = KPoint(0.0,0.0));
	KPoint      Rotate(const double& dRad,const KPoint& pt = KPoint(0.0,0.0));

	bool		InRegion(const KPoints& psRegion,const int& nType=_CW);

	KPoint&    operator =(const KPoint& pt);
	KPoint&    operator =(const double&);
	KPoint&    operator +=(const KPoint& pt);
    KPoint&    operator +=(const KVector& v);
	KPoint&    operator *=(const double& d);
	KPoint&    operator -=(const KPoint& pt);
	KPoint     operator +(const KPoint& pt);
	KPoint     operator -(const KPoint& pt);
	KPoint	   operator -() const;

	KPoint&    operator  =(const KVector& v);
	KPoint     operator  +(const KVector& v);
	KPoint     operator  -(const KVector& v);
    KPoint     operator  /(const double& d);
	KPoint     operator  *(const double& d);

	static double  Distance(const KPoint& ptO,const KPoint& ptE){ return sqrt(_SQR(ptO._dX-ptE._dX)+_SQR(ptO._dY-ptE._dY)); }    
    static double  Distance2(const KPoint& ptO,const KPoint& ptE){ return _SQR(ptO._dX-ptE._dX)+_SQR(ptO._dY-ptE._dY); }    
    static double  Distance2(const KPOINTD& ptO,const KPOINTD& ptE){ return _SQR(ptO.dX-ptE.dX)+_SQR(ptO.dY-ptE.dY); }
};

class KPoints : public KPtrList<KPoint*>
{

public:

	KPoints(int nNum=0,int nCapacity=1000) : KPtrList<KPoint*>(nCapacity,true,false){ if(nNum) Create(nNum); }

	virtual ~KPoints(){ }


	void		Create(int nNum);

	int     	Add(const KPoint& p){ return KPtrList<KPoint*>::Add(new KPoint(p)); }		
//	void        Expand(double dRate);
	KPoint      operator [] ( const int& nID) const { return *_pItems[nID]; }
	KPoint&	    operator [] ( const int& nID){        return *_pItems[nID]; }
	KPoints&	operator =  ( const KPoints& psInput);
};


//
////////////////////////////////////////////////////////////
//
// class KPoint3D
class KPoint3D //tag : pt
{
public:
	double _dX;
    double _dY;
    double _dZ;

	KPoint3D(){  };
	KPoint3D(const KPoint3D& pt){ _dX=pt._dX; _dY=pt._dY; _dZ=pt._dZ; }
	KPoint3D(const double& x, const double&y, const double& z){ _dX=x; _dY=y; _dZ=z; }
	virtual ~KPoint3D(){ }

public:
	bool    Read(FILE* fp);
	void    Write(FILE* fp);
	double  Distance(const KPoint3D& pt){ return sqrt(_SQR(pt._dX-_dX)+_SQR(pt._dY-_dY)+_SQR(pt._dZ-_dZ)); }
	double  Distance2(const KPoint3D& pt){ return (_SQR(pt._dX-_dX)+_SQR(pt._dY-_dY)+_SQR(pt._dZ-_dZ)); }
	double  Distance(const int& x,const int& y, const double& z){  return sqrt(_SQR(_dX-x)+_SQR(_dY-y)+_SQR(_dZ-z)); }
	double  Distance2(const int& x,const int& y, const double& z){ return (_SQR(_dX-x)+_SQR(_dY-y)+_SQR(_dZ-z)); }

	KPoint3D&    operator  =(const KPoint3D& pt);
	KPoint3D&    operator  =(const double& d);
	KPoint3D&    operator +=(const KPoint3D& pt);
	KPoint3D&    operator -=(const KPoint3D& pt);
	KPoint3D     operator  +(const KPoint3D& pt);
	KPoint3D     operator  -(const KPoint3D& pt);
	KPoint3D	 operator  -() const;

	KPoint3D&    operator  =(const KVector& v);
	KPoint3D     operator  +(const KVector& v);
	KPoint3D     operator  -(const KVector& v);
};

class KIDPoint : public KPoint
{
public:
	int _nID;

    KIDPoint(){ }
    KIDPoint(const int nID,const KPoint& ptIn) : KPoint(ptIn){ _nID = nID; }
    KIDPoint(const int nID,const double& x,const double& y) : KPoint(x,y){ _nID = nID; }
    virtual ~KIDPoint(){ }
};

class KIDPoint3D : public KPoint3D
{
public:
    int _nID;

    KIDPoint3D(){ }
    KIDPoint3D(const int nID,const KPoint3D& ptIn) : KPoint3D(ptIn){ _nID = nID; }
	KIDPoint3D(const int nID,const double& x,const double& y,const double& z) : KPoint3D(x,y,z){ _nID = nID; }
    virtual ~KIDPoint3D(){ }
};
//
////////////////////////////////////////////////////////////
//
// class KRect

class KRect //tag : rc
{
public:
	int _nLeft;
	int _nTop;
	int _nRight;
	int _nBottom;

	KRect(){};
	KRect(const KRect& rc){
		  _nLeft=rc._nLeft; _nTop=rc._nTop; _nRight=rc._nRight; _nBottom=rc._nBottom;
	}
	KRect(const int& x1, const int&y1,const int& x2, const int&y2){
		  _nLeft=x1; _nTop=y1; _nRight=x2; _nBottom=y2;
	}
	KRect(const KPoint& ptLT,const KPoint& ptRB){
		  _nLeft  =(int)(ptLT._dX+0.5); _nTop   =(int)(ptLT._dY+0.5);
		  _nRight =(int)(ptRB._dX+0.5); _nBottom=(int)(ptRB._dY+0.5);
	}
	virtual ~KRect(){}

	void    Create(const int& x1, const int&y1,const int& x2, const int&y2){
				   _nLeft=x1; _nTop=y1; _nRight=x2; _nBottom=y2;
	}

public:
	bool	IsValid(){ return (_nRight || _nLeft || _nBottom || _nTop ? true:false); }
	void	Invalidate(){ _nLeft = _nRight = _nTop = _nBottom = 0; }
	bool    Intersect(const KRect& rc)const {
				return (InRect(rc._nLeft,rc._nTop) || InRect(rc._nLeft,rc._nBottom) ||
						InRect(rc._nRight,rc._nTop)|| InRect(rc._nRight,rc._nBottom));
	}
	bool    Intersect(const int& x1,const int& y1,const int& x2,const int& y2)const {
				return !(_SIGN(_nRight-x1)+_SIGN(x2-_nLeft)==0 || _SIGN(_nBottom-y1)+_SIGN(y2-_nTop)==0);
	}
	bool    InRect(const KPoint& pt) const {
				return !(pt._dX<_nLeft || pt._dX>_nRight || pt._dY<_nTop || pt._dY>_nBottom);
	}
	bool    InRect(const double& dX,const double& dY) const {
				return !(dX<_nLeft || dX>_nRight || dY<_nTop || dY>_nBottom);
	}
	bool	InRect(const KRect& rcIp) const {
				return !(rcIp._nLeft<_nLeft || rcIp._nTop<_nTop ||rcIp._nRight>_nRight || rcIp._nBottom>_nBottom);
	}

	int     		Width()const { return  (_nRight-_nLeft+1); }
	int     		Height()const { return (_nBottom-_nTop+1); }
	unsigned int    Size()const { return (unsigned int)((_nRight-_nLeft+1)*(_nBottom-_nTop+1)); }
	KPoint  Center()const { return KPoint( (_nRight+_nLeft)*0.5,(_nBottom+_nTop)*0.5 ); }
	double  CenterX()const { return (_nRight+_nLeft)*0.5; }
	double  CenterY()const { return (_nBottom+_nTop)*0.5; }
	KPoint  LeftTop()const { return KPoint(_nLeft,_nTop);}
	KPoint  RightBottom()const { return KPoint(_nRight,_nBottom);}

	KRect&  MovedBy(const int& nDx,const int& nDy){ _nLeft += nDx; _nTop += nDy; _nRight += nDx; _nBottom += nDy; return *this; }
	KRect&  MovedTo(const int& nCx,const int& nCy){ MovedBy(nCx-(_nRight+_nLeft)/2,nCy-(_nTop+_nBottom)/2);  return *this; }
	KRect&  Transformed(const double& dRatio,const int& nType);
	KRect   MoveBy(const int& nDx,const int& nDy) const { return KRect(_nLeft+nDx,_nTop+nDy,_nRight+nDx,_nBottom+nDy); }
	KRect   MoveTo(const int& nCx,const int& nCy) const { return MoveBy(nCx-(_nRight+_nLeft)/2,nCy-(_nTop+_nBottom)/2); }
	KRect   Transform(const double& dRatio,const int& nType)  const ;

	KRect&  operator =(const KRect& rc);
	KRect&  operator +=(const KPoint& pt);
	KRect&  operator -=(const KPoint& pt);

};

class KRectD //tag : rc
{
public:
	double	_dLeft;
	double	_dTop;
	double	_dRight;
	double	_dBottom;

	KRectD(){};
	KRectD(const KRectD& rc){
		_dLeft = rc._dLeft; _dTop = rc._dTop; _dRight = rc._dRight; _dBottom = rc._dBottom;
	}
	KRectD(const double& x1, const double&y1, const double& x2, const double&y2){
		_dLeft = x1; _dTop = y1; _dRight = x2; _dBottom = y2;
	}
	KRectD(const KPoint& ptLT, const KPoint& ptRB){
		_dLeft = ptLT._dX; _dTop = ptLT._dY;
		_dRight = ptRB._dX; _dBottom = ptRB._dY;
	}
	virtual ~KRectD(){}

	void    Create(const double& x1, const double&y1, const double& x2, const double&y2){ _dLeft = x1; _dTop = y1; _dRight = x2; _dBottom = y2; }

public:
	bool    InRect(const KPoint& pt) const {
		return !(pt._dX<_dLeft || pt._dX>_dRight || pt._dY<_dTop || pt._dY>_dBottom);
	}
	bool    InRect(const double& dX, const double& dY) const {
		return !(dX<_dLeft || dX>_dRight || dY<_dTop || dY>_dBottom);
	}
	bool	InRect(const KRectD& rcIp) const {
		return !(rcIp._dLeft<_dLeft || rcIp._dTop<_dTop || rcIp._dRight>_dRight || rcIp._dBottom>_dBottom);
	}

	KRectD&	Transformed(const double& dRatio, const int& nType);
	int 	Width()const { return  (_dRight - _dLeft); }
	int 	Height()const { return (_dBottom - _dTop); }
};


//

////////////////////////////////////////////////////////////
//
// class KCircle
class KCircle //tag : cc
{
public:
	double	_dCx;
	double	_dCy;
	double	_dRadius;

	KCircle(){ _dCx = _dCy = _dRadius = 0.0; }
	KCircle(const KCircle& ccT){ _dCx = ccT._dCx; _dCy = ccT._dCy; _dRadius = ccT._dRadius; }
	KCircle(const KPoint& ptCen,const double& dR){ _dCx = ptCen._dX; _dCy = ptCen._dY; _dRadius = dR; }
	KCircle(const double& dCx,const double& dCy,const double& dR){ _dCx = dCx; _dCy = dCy; _dRadius = dR; }
	virtual ~KCircle(){}

	void    Create(const KPoint& ptCen,const double& dR){ _dCx = ptCen._dX; _dCy = ptCen._dY; _dRadius = dR; }
	void    Create(const double& dCx, const double& dCy,const double& dR){ _dCx = dCx; _dCy = dCy; _dRadius = dR;	}


public:
	KPoint		Center(){ return KPoint(_dCx,_dCy); }
	double&		Radius(){ return _dRadius; }
	KRect		Rect(){ return KRect((int)(_dCx-_dRadius),(int)(_dCy-_dRadius),(int)(_dCx+_dRadius),(int)(_dCy+_dRadius)); }
	KRect		RectInner(){ return KRect((int)(_dCx-_dRadius*0.707),(int)(_dCy-_dRadius*0.707),(int)(_dCx+_dRadius*0.707),(int)(_dCy+_dRadius*0.707)); }

	KCircle&	Transformed(const double& dR,int nType);
	KCircle		Transform(  const double& dR,int nType);
	bool		InCircle(const KPoint& ptTest){ return !(_SQR(ptTest._dX-_dCx)+_SQR(ptTest._dY-_dCy) > _SQR(_dRadius)); }
	bool		InCircle(const double& dX,const double& dY){ return !(_SQR(dX-_dCx)+_SQR(dY-_dCy) 	> _SQR(_dRadius)); }
	bool		InInnerRect(const double& dX,const double& dY){ return (_ABS(_dCx-dX) + _ABS(_dCy-dY) > _dRadius); }

	KCircle&  	operator =(const KCircle& cc);
};


//
////////////////////////////////////////////////////////////
//
// class KRandom

//

class KRandom   //tag : rn

{

protected:

	int		_nNum;
	int		_nIdx;
	float*	_fpRandom;

public:
	KRandom(int nNum=1000, int nType=0){ _fpRandom = 0; OnRandom(nNum,nType); }
	virtual ~KRandom(){ delete[] _fpRandom; }
public:
	void	OnRandom(int nNum,int nType=0);
	double	Generate(){ return (double)_fpRandom[_nIdx++ % _nNum]; }
};


//

////////////////////////////////////////////////////////////
//
// class KString

//

#define     _MAX_STRING_LENGTH      4097

class KString

{
	int     _nSize;
	char*   _szA;

public:
	KString(){ _nSize = 0; _szA = 0; }
	KString(const KString& stIn){ _nSize=0; _szA=0; Create(stIn._szA); }
	KString(const char* szIn){ _nSize=0; _szA=0; Create(szIn,0); }
	KString(const char* szIn,const int& nFrom, const int& nTo){ _nSize=0; _szA=0; Create(&szIn[nFrom],nTo-nFrom+1); }
	virtual ~KString(){ if(_szA) delete[] _szA; }

	void				Create(const char* szIn,const int& nSize=0);
	void				Create(const KString& stIn){ Create(stIn._szA); }
	void				Release(){ if(_szA){ delete[] _szA; _szA=0; _nSize=0; } }
	KString&    Format(const char* szFormat, ...);

public:
	//retrieve data members
    char*          Pointer() const { return _szA; }
    char*          Address() const { return _szA; }
	bool				IsEmpty() const { return (_szA ? false:true); }
    int               Size() const {    return _nSize; }

	//string operations
	int                 Find(const char*    szSub);
	int                 Find(const KString& stSub);

	//file name operations
    KString           ParentDir() const;
    KString           FilePathOnly() const;
    KString           FileNameWithoutExt() const;
    KString           FileNameWithExt() const;
    KString           FileExt() const;
	int					ToInt(){    return atoi(_szA); }
	double				ToDouble(){ return atof(_szA); }
 
  //	static KString      FilePathOnly(const char* szFile);
	static KString      FileNameWithoutExt(const char* szFile);
	static KString      FileNameWithExt(const char* szFile);
	static KString      FileExt(const char* szFile);
   
	//file IO
	bool                Write(FILE* fp,const unsigned int& nSize=0);
	bool                Read(FILE* fp,const unsigned int& nSize=0);

	//operators
	char*		        operator  ~() const { return _szA; }
						operator char*() const { return _szA; }
	KString             operator  + (const char* szStr);
	KString&            operator += (const char* szStr);
    KString&            operator += (const char& cIn);
	KString&            operator  = (const char* szStr);
	KString             operator  + (const KString& stIn);
	KString&            operator += (const KString& stIn);
	KString&            operator  = (const KString& stIn);
	bool                operator == (const KString& stIn);
	bool                operator == (const char* szIn);
	bool                operator != (const KString& stIn);
	bool                operator != (const char* szIn);
	char                operator [](const int& i) const { return _szA[i]; }
	char&               operator [](const int& i){ return _szA[i]; }

	friend KString	    operator + (const char*, const KString&);
};

class KStrings : public KPtrList<KString*>
{

public:
	KStrings() : KPtrList<KString*>(100,true,false){ };
	virtual ~KStrings(){}

	int Add(const char* szStr);

};

class KMath

{
	int     _npAtanSign[8];
	float   _fpAtanTab[8];

public:
	KMath();
	~KMath(){ };
public:
////////////////////////////////////////////////////////////////////////////////////////
//    Name:    Atan <-- based on OpenCV
//    Purpose: fast inaccurate arctangent approximation
//    Parameters:
//      y - ordinate
//      x - abscissa
//    Returns:
//      The angle of vector (x,y) in degrees (0 - 360)
//    Notes:
//      if x == 0 && y == 0 -> result is 0 too.
//      Current version accurancy: ~0.14 deg
//
   double   Atan(const float& x, const float& y)
   {
		int ix = *((int *) &x), iy = *((int *) &y);
		int ygx, idx = (ix < 0) * 2 + (iy < 0) * 4;

		ix &= 0x7fffffff;
		iy &= 0x7fffffff;

		ygx = (iy <= ix) - 1;
		idx -= ygx;

		idx &= ((ix == 0) - 1) | ((iy == 0) - 1);

		/* swap ix and iy if ix < iy */
		ix ^= iy & ygx;
		iy ^= ix & ygx;
		ix ^= iy & ygx;
		iy ^= this->_npAtanSign[idx];

		/* set ix to non zero */
		ix |= 1;

		double z = *((float *) &iy) / *((float *) &ix);
		return (_ATAN_CF0 * _ABS( z ) + _ATAN_CF1) * z + this->_fpAtanTab[idx];
	}
};

////////////////////////////////////////////////////////////////////////////////////


typedef KArray<float>	KMatrixF;

class KPoint;
class KPoint3D;
class KRect;
class KVector;
class KImageGray;
class KMatrix : public KArray<double> //tag : m
{

public:
	KMatrix(){ }
	KMatrix(const KMatrix& mMat) : KArray<double>(mMat.Row(),mMat.Col(),mMat.Pointer()){ }
	KMatrix(const int& r,const int& c) : KArray<double>(r,c){  }
	KMatrix(const int& r,const int& c,const int& t){ Create(r,c,t); }
	KMatrix(const int& r,const int& c,double* p,int m=_ALLOC) : KArray<double>(r,c,p,m){ }
	virtual ~KMatrix() { };

public:
	//memory allocation
    void    Create(const KMatrix& oMat);
    void    Create(const int& r,const int& c,const int& t=0);
	void    Create(const int& r,const int& c,double* p,int m=_ALLOC){ KArray<double>::Create(r,c,p,m); }
	//read and write the contents of the matrix
    bool    Read(FILE *fp);
    void    Write(FILE *fp) const;
	void    Write(const char *szFile,const char* szMode=0) const;
    void    WriteText(KStrings& ssBuf,const char* szFormat=0) const;
	void    WriteText(FILE *fp,const char* szFormat=0) const;
	bool    WriteText(const char* szFile,const char* szFormat=0,const char* szMode=0) const;


///////////////////////////////////////////////////////////
//setting operations
//
	//swap i row(col) and  j row(col)
	void  Swap(int i,int j,int nType);
	//set matrix according to a given type
	void  Set(int nType);
	void  Set(double nVal,int nIdx,int nType);

	//place a given matrix on (nRow,nCol)
	KMatrix& Place(int nRow,int nCol, const KMatrix& oMat);
	KMatrix& Place(int nRow,int nCol, const KPoint& pt);
	KMatrix& Place(int nRow,int nCol, const KPoint3D& pt);

	//transform into the vector form
	KVector Vector() const;


//////////////////////////////////////////////////////////
//getting operations
//
	//extraction
    void        Column(int c,KVector& vOut) const;
    KVector     Column(int c) const;
    void        RowVec(int r,KVector& vOut) const;
    KVector     RowVec(int r) const;
    KMatrix     Sign() const;

    KMatrix     Cut(int r,int c,int r2,int c2) const;
    KMatrix		Cut(int i,int nType) const; //nType: _COL,_ROW
    KMatrix     From(int r,int c) const;
    KMatrix     To(int r2,int c2) const;
    KMatrix		Min(const int& nType) const;
    KMatrix		Max(const int& nType) const;

	//get diagonalized forms
    KMatrix        Diag();
	KMatrix 	   Abs();
	static KMatrix Diag(const double& d1,const double& d2);
	static KMatrix Diag(const double& d1,const double& d2,const double& d3);
	static KMatrix Diag(const KVector& v);
	static KMatrix Diag(const int& n,const double* );
	static KMatrix Diag(const KMatrix& mMat1,const KMatrix& mMat2);
	static KMatrix Diag(const KMatrix& mMat1,const KMatrix& mMat2,const KMatrix& mMat3);
	static KMatrix RepMat(const KMatrix& mMat,const int& nRow,const int& nCol);
	static KMatrix RepMat(const double&,const int& nRow,const int& nCol);
	static KMatrix Ones(const int& r, const int& c);
    static KMatrix Kron(const KMatrix& mX, const KMatrix& mY);
    //static KMatrix MeshGrid(const KVector& vX, const KVector& vY);
    //static KMatrix MeshGrid(const KVector& vX, const KVector& vY);

//////////////////////////////////////////////////////////
//mathmatical operations
//
	//inversion
    void        Iv(KMatrix&);
    KMatrix     Iv();
	KMatrix     IvDefault();
	//diagonalize
	KMatrix		Diagonalize();
	//normalize
    void        Normalized(const int& nType); //행방향 혹은 열방향 벡터의 정규화
	//tranpose
    KMatrix     Tr();
	//speed calculation of mA*mA.Tr()
    KMatrix     Cor();
	KMatrix     Sc1();
	//decomposition
	KMatrix	    Cholesky();
	bool        QR(KMatrix& mQ,KMatrix& mR); //returns a 3x3 upper triangular mR and a unitary mQ so that X = Q*R
	bool		RQ(KMatrix& mR,KMatrix& mQ); //returns a 3x3 upper triangular mR and a unitary mQ so that X = R*Q
	double	    LU(int* nIp);
	bool        SVD(KMatrix& mU,KVector& vW,KMatrix& mV);


	//etc.
	double      Det()   const; 	//determinant
	double      Trace() const; 	//trace
	KVector		Sum()   const;  //column-wise sum

	//eigen values and vectors for real and symetric matrics
	bool		Eigen(KMatrix& mEigen, KVector& vEigen);
	//generalized eigen problem( mA*vEigen = dEigen*mB*vEigen )
	KVector     Eigen(KMatrix& mA,KMatrix& mB);
	double		Pythag(double a, double b);

	//sparse matrix - referenced to chap.2 of "Numerical Recipes in C"
	void		    ToSparseMode(KList<double>& lA, KList<unsigned int>& lIdx, const double& dThresh=0.0);
	static KVector  SparseAX(const KList<double>& lA,  const KList<unsigned int>& lIdx,const KVector& vX);
	static KVector  SparseATX(const KList<double>& lA, const KList<unsigned int>& lIdx,const KVector& vX);
	static KVector  SparseAsolve(const KList<double>& lA, const KList<unsigned int>& lIdx,const KVector& vB);
	static double  	LinBCG(KList<double>& lA, KList<unsigned int>& lIdx,const KVector& vB,KVector& vX,const int& nITR,const double& dTOL);
///////////////////////////////////////////////////////////
//operators
//
	int			operator ==(const KMatrix&);
	int			operator !=(const KMatrix&);
	KMatrix&	operator  =(const KMatrix&);
	KMatrix&	operator +=(const KMatrix&);
	KMatrix&	operator -=(const KMatrix&);
	KMatrix&	operator *=(const double&);
	KMatrix&	operator *=(const KMatrix&);
	KMatrix&	operator /=(const double&);
	KMatrix&	operator /=(const KMatrix&);      // ./ as in MatLab
	KMatrix&    operator  =(const double&);
	KMatrix	    operator  *(const KMatrix&) const;
	KVector     operator  *(const KVector&) const;
	KVector	    operator  *(const KPoint&)  const;
	KMatrix	    operator  +(const KMatrix&) const;
	KMatrix	    operator  &(const KMatrix&) const;  //element-wise multiplication

	KMatrix	    operator  +(const double&) const;
	KMatrix	    operator  -(const double&) const;
	KMatrix	    operator  *(const double&) const;
	KMatrix	    operator  /(const double&) const;

	KMatrix 	operator  /(const KMatrix&) const;       // ./ as in MatLab
	KMatrix	    operator  -(const KMatrix&) const;
	KMatrix&    operator  |=(const KMatrix&);      // add a column
	KMatrix	    operator  |(const KMatrix&);       // add a column
	KMatrix	    operator  ^(const KMatrix&);       // add a row
	KMatrix&	operator  ^=(const KMatrix&);
	KMatrix&	operator  ^=(const double&);       //element-wise exponential computation
	KMatrix	    operator  ^(const double&);
	KMatrix	    operator  -() const;               // * (-1)
	KMatrix	    operator  ~() const;                // inverse


	friend KMatrix	operator * (const double&, const KMatrix&);
};

class KMatrices : public KPtrList<KMatrix*>
{

public:

	KMatrices(int nNum=0,int nCapacity=1000) : KPtrList<KMatrix*>(nCapacity,true,false){ if(nNum) Create(nNum); }

	virtual ~KMatrices(){ }


	void		Create(int nNum); 
	int     	Add(const KMatrix& m);

	void		WriteText(const char* szFile);


	KMatrix&	operator [](const int& nID){        return *_pItems[nID]; }
	KMatrix     operator [](const int& nID) const { return *_pItems[nID]; }
	KMatrices&  operator = (const KMatrices& msInput);

};

/*
class KSMatrix  //tag: sm - sparse matrix
{
	KList<double>& 		 lA;
	KList<unsigned int>& lIdx;

public:
	KSMatrix(){ }
	KSMatrix(const KMatrix& mA){ Create(mA); }
	virtual ~KSMatrix(){ }

	void Create(const KMatrix& mA);
	KSMatrix&    operator  =(const double&);
*/

//
////////////////////////////////////////////////////////////
//
// class KVector
//
class KImageGray;
class KVector : public KMatrix //tag : v
{
public:
	KVector(){ }
	KVector(const int& nDim) : KMatrix(nDim, 1){ };
	KVector(const int& nDim,double* pAdd,int nMode=_ALLOC) : KMatrix(nDim,1,pAdd,nMode){ };
	KVector(const KPoint& pt) : KMatrix(2,1){ _ppA[0][0]=pt._dX; _ppA[1][0]=pt._dY; }
	KVector(const KPOINT3F& pt) : KMatrix(3,1){ _ppA[0][0]=pt.fX; _ppA[1][0]=pt.fY; _ppA[2][0]=pt.fZ; }
	KVector(const KCOLOR32& pt) : KMatrix(3,1){ _ppA[0][0]=pt.r; _ppA[1][0]=pt.g; _ppA[2][0]=pt.b; }
	KVector(const KCOLOR24& pt) : KMatrix(3,1){ _ppA[0][0]=pt.r; _ppA[1][0]=pt.g; _ppA[2][0]=pt.b; }
    KVector(const KList<double>& lData){ Create(lData); }
	KVector(const KRect& rc) : KMatrix(4,1){ _ppA[0][0]=rc._nLeft; _ppA[1][0]=rc._nTop;_ppA[2][0]=rc._nRight;_ppA[3][0]=rc._nBottom; }
	KVector(const double& d1, const double& d2) : KMatrix(2,1){ _ppA[0][0] = d1; _ppA[1][0] = d2;}
	KVector(const double& d1, const double& d2, const double& d3) : KMatrix(3,1){
		_ppA[0][0] = d1; _ppA[1][0] = d2; _ppA[2][0] = d3;
	}
	KVector(const double& d1, const double& d2, const double& d3,const double& d4) : KMatrix(4,1){
		_ppA[0][0] = d1; _ppA[1][0] = d2; _ppA[2][0] = d3; _ppA[3][0] = d4;
	}
	KVector(const double& d1, const double& d2, const double& d3,const double& d4,const double& d5) : KMatrix(5,1){
		_ppA[0][0] = d1; _ppA[1][0] = d2; _ppA[2][0] = d3; _ppA[3][0] = d4; _ppA[4][0] = d5;
	}

	KVector(const KMatrix& mMat) : KMatrix(mMat.Size(),1,mMat.Pointer()) { }
	KVector(const KVector& oVec) : KMatrix(oVec.Row(),1,oVec.Pointer())  { };
	virtual ~KVector() { };

public:
	//getting functions
	int     Dim()const { return Row(); };  //dimension
	void    Angle(double& a,double& b,double& c,int nType=_DEG); //direction angle(-180 ~ 180)
	double  Angle(int nType = _DEG); // -180 ~ 180

	//memory allocation
	void	Create(const int& nDim);
	void	Create(const int& nDim,double* pV,int nMode=_ALLOC);
    void    Create(const KList<double>& lData);
    void    Create(const double& d1, const double& d2){
                KMatrix::Create(2,1); _ppA[0][0] = d1; _ppA[1][0] = d2;
            }
    void    Create(const double& d1, const double& d2, const double& d3){
				KMatrix::Create(3,1);
				_ppA[0][0] = d1; _ppA[1][0] = d2; _ppA[2][0] = d3;
			}
    void    Create(const double& d1, const double& d2, const double& d3,const double& d4){
				KMatrix::Create(4,1);
				_ppA[0][0] = d1; _ppA[1][0] = d2; _ppA[2][0] = d3; _ppA[3][0] = d4;
			}
    void    Create(const double& d1, const double& d2, const double& d3,const double& d4,const double& d5){
				KMatrix::Create(5,1);
				_ppA[0][0] = d1; _ppA[1][0] = d2; _ppA[2][0] = d3; _ppA[3][0] = d4; _ppA[4][0] = d5;
			}

	//file io
	bool		Read(FILE* fp);
	bool		Read(char* szFile);
	void		Write(FILE* fp) const;
	void    	Write(const char *szFile,const char* szMode=0) const;
	void		WriteText(FILE* fp,const char* szFormat=0) const;
	void    	WriteText(char* szFile,const char* szFormat=0,const char* szMode=0) const;
   //operations
	KVector     From(int nRow) const;
	KVector     To(int nRow) const;

    void				Sort(int nType,int nNum=0); //nNum: required number of elements sorted, "0" means full sorting
	KVector		Cut(int nFrom,int nTo) const;
	KVector		Insert(int r,double d) const;
	KVector		Tail(double d) const;
    KVector&	Tailed(double d);
	KVector		Tail(const KVector& v) const;
    KVector&    Tailed(const KVector& v);
    KVector		Floor() const;
    KVector&	Floored();

    void        Place(int r,const KMatrix& v){ KMatrix::Place(r,0,v); }
//    void        Trim(int nDummy){ Row() = (Row()-1 > nDummy ? nDummy : Row()); } //neglect elements from the nDummy time
	KMatrix     Skew(); //skew symetric matrix:  a x b = a.Skew() * b
	//math    
    double      Average();
    double      Variance();
    void 		Statistics(double& dMean, double& dVar);
	double      Median(const int& nType=_MEDIAN_RANK,const int& nTo=0);
    KVector&    MedianFiltered(const int& nWindow);
	double      Max(int* npIdx = 0,int nMode = _DEFAULT);  //nMode: _DEFAULT, _ABSOLUTE
	double      Min(int* npIdx = 0,int nMode = _DEFAULT);
	double      Sum() const;
    double		Norm2() const;              // V'* V
    double	    Norm2(const KMatrix& mA) const;  // V'* mA * V
    KVector&    Normalized(int nMode,double* dpOut=0);
    KVector     Normalize(int nMode) const;

	static double 	Distance2(const KVector& v1,const KVector& v2);
	static KVector  Min(const KVector& v1,const KVector& v2);
	static KVector  Max(const KVector& v1,const KVector& v2);

	//operator
    KVector&    operator  =(const KList<double>&);
	KVector&    operator  =(const KImageGray&);
	KVector&    operator  =(const KPoint&);
	KVector&    operator  =(const KCOLOR32&);
	KVector&    operator  =(const KCOLOR24&);
	KVector&    operator  =(const double&);
	KVector     operator  +(const KMatrix&) const;
	KVector     operator  -(const KMatrix&) const;
	KVector     operator  +(const KVector&) const;
	KVector     operator  -(const KVector&) const;
	KMatrix     operator  *(const KMatrix&) const;
	KVector     operator  /(const KVector&) const;
	KVector     operator  *(const double&)  const;
	KVector     operator  /(const double&)  const;
	KVector	    operator  -() const;                // * (-1)
    double      operator  &(const KVector&) const; //inner product
    double      operator [](const int& i) const { return _ppA[i][0];}
	double&     operator [](const int& i){ return _ppA[i][0];}

	friend KVector	operator * (const double&, const KVector&);
};

class KVectorS : public KArray<short>
{
    int _nDim;

public:
    KVectorS(){  _nDim =0; }
    KVectorS(const KVectorS& vIn) : KArray<short>(1, vIn.Dim(), vIn.Address()) {  _nDim = vIn.Dim(); }
    KVectorS(const int& nDim) : KArray<short>(1, nDim){  _nDim = nDim; };
    KVectorS(const int& nDim, short* spAdd,int nMode=_ALLOC) : KArray<short>(1, nDim, spAdd,nMode){  _nDim = nDim; }
    virtual ~KVectorS(){ }

    void    Create(const int& nDim){ KArray<short>::Create(1,  nDim); _nDim = nDim;  }
    void    Create(const int& nDim, short* spAdd, int nMode=_ALLOC) { KArray<short>::Create(1,  nDim, spAdd, nMode); _nDim = nDim; }

    double      Norm2();
	double		 SumAbs();
    int             Dim() const { return _nDim; }

	short      operator [](const int& i) const { return _ppA[0][i];}
	short&   operator [](const int& i){ return _ppA[0][i];}
};

class KVectors : public KPtrList<KVector*>
{

public:
	KVectors(int nNum=0,int nCapacity=1000) : KPtrList<KVector*>(nCapacity,true,false){ if(nNum) Create(nNum); }

	virtual ~KVectors(){ }


	void		Create(int nNum);

	int     	Add(const KVector& v);


	KVector&	operator [](const int& nID){        return *_pItems[nID]; }

	KVector     operator [](const int& nID) const { return *_pItems[nID]; }

};


class KIDVector : public KVector

{
public:
	int _nID;

	KIDVector(){ }
    KIDVector(const int nID,const KVector& vIn) : KVector(vIn) { _nID = nID; }
    KIDVector(const KIDVector& vIn) : KVector(vIn) { _nID = vIn._nID;   }
	virtual ~KIDVector(){ }

	int& 	ID(){ return _nID; }
	void	Write(FILE* fp){ fwrite(&_nID,sizeof(int),1,fp); KVector::Write(fp); }
	bool    Read(FILE* fp){ if(fread(&_nID,sizeof(int),1,fp) != 1) return false; return KVector::Read(fp); }

};



class KImageDouble;
class KImageColor;
class KImageColor24;
class KMask;
class KImageGray : public KArray<unsigned char>

{

public:
	KImageGray(){};
	KImageGray(int row,int col) : KArray<unsigned char>(row,col){ }
	KImageGray(int row,int col,unsigned char* p,int t=_ALLOC) : KArray<unsigned char>(row,col,p,t){ }
	virtual ~KImageGray(){};

	KImageGray& Cleared(const KRect& rcArea,const int& nType = _INWARD); //set the given area to 0
	KImageGray& Cleared(){ if(_ppA) memset(_ppA[0],0,Size()); return *this; }
	KImageGray& Activated(const KRect& rcArea,const int& nType = _INWARD); //set the given area to 255
	KImageGray& Activated(){ if(_ppA) memset(_ppA[0],0xFF,Size()); return *this; }


	KImageGray  Crop(int jx, int iy, int nWidth, int nHeight) const;
	KImageGray  Crop(const KRect& rcCrop) const;
    void        Crop(const KRect& rcCrop,KImageGray& igOut) const;
    void        Crop(int nXi,int nYi, int nWidth,int nHeight,KImageGray& iaOut) const;
    void        Crop(int nXi,int nYi, int nWidth,int nHeight,KVector& vOut) const;
    void        Place(int nXi,int nYi,const KImageGray&);

    bool        InImage(const double& dX, const double& dY) const { if(dX<0.0 || dX > Col()-1 || dY<0.0 || dY > Row()-1 ) return false; return true; }
	KImageGray  Rotate(const double& dRad,const double& dXo=0.0, const double& dYo=0.0) const;
	KImageGray  Rotate(const double& dRad,const KPoint& pt=KPoint(0.0,0.0)) const;
    KImageGray  Transform(const KMatrix& mHomography)   const;
    KImageGray& Transformed(const KMatrix& mHomography);

    void        HalfSize(KImageGray& igHalf);
    KImageGray  HalfSize();
	KImageGray  StretchN(int nRow,int nCol) const;
	KImageGray  Stretch(int nRow,int nCol) const;
    void        Stretch(int nRow,int nCol,KImageGray& igOut,bool bMedian = false) const;
    void        Stretch(int nRow,int nCol,KVector& vOut) const;

    KImageColor GrayToRGB();
    void        GrayToRGB(KImageColor& icOut);
    void        Threshold(const int& nThresh, KImageGray& igOut);
    KImageGray& Thresholded(const int& nThresh);
    KImageGray  BinaryDilate(const int& nType);
    KImageGray  BinaryErode(const int& nType);
    void        BinaryDilated(const int& nType);
    void        BinaryEroded(const int& nType);
    KImageGray  GrayDilate(){ return KImageGray(); }
    void        GrayDilated(){ }
    KBlobList*  BlobColoring(int nType, KRect* rcpScan=0,KImageColor* icpColor=0);
    KBlobNList* Boundaries(int nType, KRect* rcpScan=0) const;
    KImageGray  Solarize(); //픽셀값 반전
    KImageGray& Solarized();

    void        Vectorize(KMask& oMask,KVector& vOut,bool bMedian);
    void        Vectorize(KVector& vOut,bool bMedian = false);
    KVector     Vectorize(bool bMedian = false);

    unsigned char   BilinearInterpolation(const double& dU,const double& dV) const;
    void            BilateralFiltered(const double& dSigmaS, const double& dSigmaR);
    double          LoGFiltered(int nWinSize,double dSigma,double dOffset);
    KImageGray      ContrastTransform(const int& nA, const int& nB,const int& nAp=0, const int& nBp=255);
    KImageGray&     LogarithmTransformed();
    void            MaxValueFiltered(int nMaskSize);
    void            MinValueFiltered(int nMaskSize);
    void            Convolution(const KArray<double>& arMask,KImageDouble& idOut);
    KImageGray&     GaussianSmoothed(const double& dSigma);
    KImageGray      GaussianSmoothing(const double& dSigma);
    KImageGray&     MedianFiltered(int nWindow=3);
    KImageGray      MedianFiltering(int nWindow=3);

    KImageGray&     operator  =(const unsigned char&);
    KImageGray&     operator  =(const KImageColor24&);
    KImageGray&     operator  =(const KImageColor&);
};

class KImageDisparity : public KImageGray //tag: id
{
	double  _dFocal;
	double  _dBaseline;
	KPoint  _ptCen;

	//intermediate
	double  _dScale;

public:
	KImageDisparity(){};
	KImageDisparity(int r,int c,const KPoint& ptCen,double dF,double dBase){ Create(r,c,ptCen,dF,dBase); }
    virtual ~KImageDisparity(){};

    void         Create(int row,int col,const KPoint& ptCen,double dFocal,double dBaseline);
    double      Xc(const int& x,const int& y){ return ((double)x-_ptCen._dX)*_dBaseline/(double)(_ppA[y][x]); }
    double      Yc(const int& x,const int& y){ return ((double)y-_ptCen._dY)*_dBaseline/(double)(_ppA[y][x]); }
	double      Zc(const int& x,const int& y){ return _dScale/(double)(_ppA[y][x]); }
	KPoint3D    Depth(const int& x,const int& y);
    void          Depth(const int& x,const int& y,KPoint3D& ptDepth);

    KImageDisparity& operator = (const KImageDisparity&);
};

class KImageTriplet;
class KImageColor24;
class KImageColor : public KArray<KCOLOR32>
{

public:
	KImageColor(){ }
	KImageColor(int row,int col) : KArray<KCOLOR32>(row,col){ }
	KImageColor(int row,int col,KCOLOR32* p,int t=_ALLOC) : KArray<KCOLOR32>(row,col,p,t){ }
	virtual ~KImageColor(){ }

    void            Create(int row,int col){ KArray<KCOLOR32>::Create(row,col); }
    void            Create(int row,int col,KCOLOR32* p,int t=_ALLOC){ KArray<KCOLOR32>::Create(row,col,p,t); }

    void            SetIndex(int id){ sprintf(_szNote,"%d",id); }
    int             Index(){ return atoi(_szNote); }
    void            Stretch(int row,int col,KImageColor& icOut);
    void            SplitInto(KImageGray& igR,KImageGray& igG,KImageGray& igB) const;
    KImageGray      RedBand();
    KImageGray      GreenBand();
    KImageGray      BlueBand();
    KTRIPLET        BilinearInterpolation(const double& dU,const double& dV) const;

    bool            InImage(const double& dX, const double& dY) const { if(dX<0.0 || dX > Col()-1 || dY<0.0 || dY > Row()-1 ) return false; return true; }

    void            RGBtoYUV(KArray<KYUV>& arYUV) const;
    void            RGBtoYUV(const int& x,const int& y,KYUV& oYUV) const;
    void            RGBtoYUV(KImageGray& igY,KImageGray& igU,KImageGray& igV) const;
    void            RGBtoHSI(KArray<KHSI>& arHSI) const;
    void            RGBtoHSV(KArray<KHSV>& arHSV) const;
    KImageColor&    FromHSV(KArray<KHSV>& arHSV);
    void            RGBtoHSI(const int& x,const int& y,KHSI& oHSI) const;
    void            RGBtoIRG(KArray<KIRG>& arIRG) const;
    void            ColorToGray(KImageGray& igOut) const;
    KImageGray      ColorToGray() const;
    double          Intensity(const int& x, const int& y) const
	{
					return (0.299*_ppA[y][x].r + 0.587*_ppA[y][x].g + 0.114*_ppA[y][x].b);
	}
    void            ToColor24(KImageColor24& icImg) const;
    void            Crop(const KRect& rcCrop,KImageTriplet& itOut,bool bNormalize=false) const;
    void            Crop(const KRect& rcCrop,KImageColor& icOut) const;
    void            Crop(const KRect& rcCrop,KImageGray&  igOut,int nType=_GRAY) const;
    void            Log(KImageTriplet& itOut);
    void            Convolution(const KArray<double>& arMask,KImageTriplet& itOut);
    KImageColor&    GaussianSmoothed(const double& dSigma);
    KImageColor     GaussianSmoothing(const double& dSigma);
};

class KImageColor24 : public KArray<KCOLOR24>
{
public:
	KImageColor24(){};
	KImageColor24(int row,int col) : KArray<KCOLOR24>(row,col){ }
	KImageColor24(int row,int col,KCOLOR24* p,int t=_ALLOC) : KArray<KCOLOR24>(row,col,p,t){ }

    virtual ~KImageColor24(){}

    void            Create(int row,int col);
    void            Create(int row,int col,KCOLOR24* p,int t=_ALLOC);
    void            SetIndex(int id){ sprintf(_szNote,"%d",id); }
    int               Index( ){ return atoi(_szNote); }
    void            SplitInto(KImageGray& igR,KImageGray& igG,KImageGray& igB) const;
    KTRIPLET   BilinearInterpolation(const double& dU,const double& dV) const;

    bool                InImage(const double& dX, const double& dY){ if(dX<0.0 || dX > Col()-1 || dY<0.0 || dY > Row()-1 ) return false; return true; }

	void        RGBtoYUV(KArray<KYUV>& arYUV) const;
    void        RGBtoYUV(KImageGray& igY,KImageGray& igU,KImageGray& igV) const;
	void        RGBtoHSI(KArray<KHSI>& arHSI) const;
    void        RGBtoHSV(KArray<KHSV>& arHSV) const;
	void        RGBtoHSI(const int& x,const int& y,KHSI& oHSI) const;
	void        RGBtoIRG(KArray<KIRG>& arIRG) const;
	void        ColorToGray(KImageGray& igOut) const;
    void            ToColor32(KImageColor& icImg) const;
    KImageColor ToColor32() const;
    void            Crop(const KRect& rcCrop,KImageColor24& icOut) const;
    void            Crop(const KRect& rcCrop,KImageGray&  igOut) const;
	KImageGray  ColorToGray() const;
};

class KImageDouble : public KArray<double>
{
public:

	KImageDouble(){};
	KImageDouble(int row,int col) : KArray<double>(row,col){ }
	KImageDouble(int row,int col,double* p,int t=_ALLOC) : KArray<double>(row,col,p,t){ }
	KImageDouble(const KImageDouble& idImg) : KArray<double>(idImg.Row(),idImg.Col(),idImg.Pointer()){ }
	KImageDouble(const KImageGray& igImg,const int& nOption =_NO_SCALING);
	virtual ~KImageDouble(){};

					// _NO_SCALING         0
					// _DEFAULT_SCALING    1
					// _USER_SCALING       2
    void          Write(KImageGray& igImg,int nOption=_NO_SCALING,int nSi=0,int nSf=255,double dMin=0.0,double dMax=0.0);
    void          ScaleTo(KImageGray& igImg,int nOption=_NO_SCALING,int nSi=0,int nSf=255,double dMin=0.0,double dMax=0.0)
					{  Write(igImg,nOption,nSi,nSf,dMin,dMax); }
	void			ToGray(KImageGray& igImg,int nOption=_NO_SCALING,int nSi=0,int nSf=255,double dMin=0.0,double dMax=0.0)
					{  Write(igImg,nOption,nSi,nSf,dMin,dMax); }
    KImageGray	ToGray(int nOption=_NO_SCALING,int nSi=0,int nSf=255,double dMin=0.0,double dMax=0.0)
					{  KImageGray igOut; Write(igOut,nOption,nSi,nSf,dMin,dMax); return igOut; }

					//parameters
					// - nType : _ROW, _COL
					// - vKernel : dimension is odd
					// - mKernel : dimension is odd, column size = row size
    void              Convolution(const double& dSigma,const int& nType,const bool& bExcludeBound,KImageDouble& idOut){ };
    void              Convolution(const KVector& vKernel,const int& nType,const bool& bExcludeBound,KImageDouble& idOut);
    void              Convolution(const KMatrix& mKernel,const bool& bExcludeBound,KImageDouble& idOut);
    KImageDouble Convolution(const KVector& vKernel,const int& nType,const bool& bExcludeBound);
    KImageDouble DoubleSize();
    KImageDouble HalfSize();
	double          Pixel(const double& dX,const double& dY) const;

    KImageDouble     Log();
	KImageDouble&   operator  = (const KImageGray& igImg);
	KImageDouble&   operator -= (const KImageDouble& idImg);
    KImageDouble     operator  - (const KImageDouble& idImg);

};

typedef struct tagKBINARIZATION_OUTPUT
{
    int         nThresh;
    double   dMyuG;  //전역 평균
	double	dMyu1;  //영역 1 평균
	double	dMyu2;  //영역 2 평균 ( > 영역 1 평균 )
    double   dQ1;
    double   dQ2;

}KBINARIZATION_OUTPUT;

class KHisto : public KVector  //tag: h
{
	KBINARIZATION_OUTPUT	_oOstuOutput;

public:
	KHisto(){}
	KHisto(const int& nSize){ KVector::Create(nSize); }
	KHisto(const KImageGray& igImg){ Histogram(igImg); }
	KHisto(const KHisto& oHisto){ KVector::Create(oHisto.Size(),oHisto.Pointer()); }
	virtual ~KHisto(){}

	//operations
	void        	Histogram(const KImageGray& igImg,const int& nType=_GRAY,const int& nDir=-1,const int& nS=0,const int& nE=0);               
	void        	Histogram(const KPtrList<KImageGray*>& plImg);
	void        	HEQ(KImageGray&  igImg, bool bSetHisto = false);
	void        	HEQ(KImageColor& icImg, bool bSetHisto = false){ };

    double                           Mean();
	KBINARIZATION_OUTPUT*	Ostu(const KImageGray* igpImg=0,KImageGray* igpOut=0);
	KBINARIZATION_OUTPUT*	Ostu(const KListPixel* lpPixel);    

//	KHisto&     operator = (const double& dSet);
};


class KMask
{
	// Attributes
public:
	enum eMaskType { CIRCLE, ELLIPSE, OVAL, RECTANGLE };

private:
	int					_nWidth;
	int					_nHeight;
	int					_nMaskSize;
	eMaskType				_nMaskType;
	KArray<unsigned char>		_arMask;
	KVector				_vMasked;

	// Constructor & Destructor
public:
	KMask();
	KMask(eMaskType nMaskType);
	virtual ~KMask() {}

	// Operations
protected:
	void		ScanMaskSize();

public:
	eMaskType	Type() { return _nMaskType; }
	int			Width() const { return _nWidth; }
	int			Height() const  { return _nHeight; }
	int			MaskSize() const { return _nMaskSize; }

	bool		Background(int x, int y) const { return ( _arMask[y][x]  ? false : true); }
	KVector		Masking(KVector& vIn, KRect& rcRect);

	void			Init(unsigned char* pSrc,const int& nWidth,const int& nHeight);

	KMask&   operator = (const KMask& oMask);

};

class KImageTriplet : public KArray<KTRIPLET>
{


public:

	KImageTriplet(){};

	KImageTriplet(int row,int col) : KArray<KTRIPLET>(row,col){  }
	virtual ~KImageTriplet(){};

	void            Create(int row,int col){ KArray<KTRIPLET>::Create(row,col); }

	KImageDouble    RedBand();
	KImageDouble    GreenBand();
	KImageDouble    BlueBand();

	void            Convolution(const KArray<double>& arMask,KImageTriplet& itOut);
	void            Log(KImageTriplet& itOut);
	void            Exp(KImageTriplet& itOut);
	KImageTriplet   Convolution(const KArray<double>& arMask);
	KImageTriplet   Log();
	KImageTriplet   Exp();

	void            Write(KImageGray& igImg,int nBand,int nOption,int nSi=0,int nSf=0,double dMin=0.0,double dMax=0.0);
						 //nBand : _RED, _GREEN, _BLUE
						 //nOption : _NO_SCALING, _DEFALT_SCALING, _USER_SCALING
	//
	void            Tmp(KImageColor& icImg,KImageTriplet& itIni,KImageTriplet& itLpc);
};

class KImageWord : public KArray<unsigned short>
{
public:

	KImageWord(){};
	KImageWord(int row,int col) : KArray<unsigned short>(row,col){  }
	KImageWord(int row,int col,unsigned short* p) : KArray<unsigned short>(row,col,p){  }
	virtual ~KImageWord(){};

	void            Create(int row,int col){ KArray<unsigned short>::Create(row,col); }
	void            Create(int row,int col,unsigned short* p){ KArray<unsigned short>::Create(row,col,p); }

	void			ScaleTo(KImageGray& igImg,const unsigned short& wMax=0);
	KImageWord&		BilateralFiltered(const double& dSigmaS, const double& dSigmaR);
	KImageWord&		HybridFiltered(const double& dSigmaS, const double& dSigmaR);
	KImageWord&		MedianFiltered(const double& dSigmaS);

	KImageWord&		operator = (const unsigned short& wIn);
};
/////////////////////////////////////////////////////////////////////////////////

class KPGM : public KImageGray //tag : gm
{
	KImageWord	_iwImg;  //for a 16bit PGM file
	double		_dScale;

public:
	KPGM( ){ }
	KPGM(int row,int col) : KImageGray(row,col){ }
	KPGM(const KImageGray & igImg) : KImageGray(igImg.Row(),igImg.Col(),igImg.Pointer()){ }
	KPGM(const KImageWord & iwImg);
    KPGM(const char* szName){ Load(szName); }
	virtual ~KPGM(){ }

public:
	virtual bool   	Load(const char* szName);
	void	        Save(const char* szName);

	KImageWord&		ImageWord(){ return _iwImg; }
	void			UpdateData();

	KPGM&   operator  =(const KImageGray&);
	KPGM&   operator  =(const KImageWord&);
	KPGM&   operator  =(KPGM&);
};



class KPPM : public KImageColor //tag : pm
{
public:
	KPPM( ){ };
	KPPM(char* szName){ Load(szName); }
	KPPM(int nRow,int nCol) : KImageColor(nRow,nCol){ }
	KPPM(const KImageColor& oImg) : KImageColor(oImg.Row(),oImg.Col(),oImg.Pointer()){ }
	~KPPM(){ };

public:
	virtual bool   	Load(const char* szName);
	void	        Save(const char* szName);

	KPPM&  operator  =(const KImageColor&);
};


/////////////////////////////////////////////////////////////////////////////////
class KDib
{
	int             _nWidth;
	int             _nHeight;	
	int             _nBitCount;	
	unsigned long   _dwImgSize;
	unsigned long   _dwDibSize;	
	unsigned char* 	_pDib;
    KImageGray		_igImg;
    KImageColor24   _icImg;


public:
	KDib(void);
	KDib(const KDib& dib);
    KDib(const char* szFile){ _pDib = 0; Load(szFile); }
    KDib(int nWidth, int nHeight, int nBitCount,void* pInit=0){ _pDib = 0; Create(nWidth,nHeight,nBitCount,pInit); }
	~KDib(void);

	//BMP 파일 불러오기/저장하기
    bool        Load(const char* szFileName);
    bool        Save(const char* szFileName);

	//이미지 생성 및 소멸
    bool 		Create(int nWidth, int nHeight, int nBitCount,void* pInit=0);
    void		Release();
    void		UpdateData();


	// 픽셀 데이터 시작 포인터 반환
    void*     DibBitsAddr();

	// 이미지 정보 반환 함수
    KImageGray&    ImageGray()   { return _igImg;  }
    KImageColor24& ImageColor() { return _icImg;  }

    int         Height()     const   { return _nHeight;   }
    int         Width()      const   { return _nWidth;    }
    int         BitCount()  const { return _nBitCount; }
    int         DibSize()   const { return _dwDibSize;  }
    int			ImgSize()   const { return _dwImgSize; }
    bool        IsValid()   const { return (_pDib != 0); }

public:
	KDib&       operator=(const KDib& dib);

/*
#ifdef _WIN32
	// 이미지 화면 출력
	void        Draw(HDC hDC);
	void        Draw(HDC hDC, int dx, int dy);
	void        Draw(HDC hDC, int dx, int dy, int dw, int dh, DWORD dwRop = SRCCOPY);
	void        Draw(HDC hDC, int dx, int dy, int dw, int dh,int sx, int sy, int sw, int sh, DWORD dwRop = SRCCOPY);    
#endif
*/
};
///////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////
//
// class KRotation

class KRotation : public KMatrix //tag : r
{
public:
   KRotation() : KMatrix(3,3,_IDENTITY){ }
   KRotation(const KMatrix& mMat):KMatrix(mMat.Row(),mMat.Col(),mMat.Pointer()){  }
   KRotation(const double& a,const double& b,const double& c,const int& nT) : KMatrix(3,3){ FromEuler(a,b,c,nT); }
   KRotation(const double& a, const double& b,const double& c,const double& d) : KMatrix(3,3){ FromQuarternion(a,b,c,d); }
   KRotation(const int& nAxis,const double& dRad) : KMatrix(3,3){ FromAxisRotation(nAxis,dRad); }
   virtual ~KRotation(){}

   KRotation&	FromAxisRotation(const int& nAxis,const double& dRad);
   KRotation&	FromAxisRotation(const double& nx,const double& ny,const double& nz,const double& dRad);
   KRotation&	FromAxisRotation(const KVector& vR,const double& dRad){ return FromAxisRotation(vR[0],vR[1],vR[2],dRad); }
   KRotation&	FromRodrigues(const double& a,const double& b,const double& c);
   KRotation&	FromEuler(const double& yaw,const double& pitch,const double& roll,const int& nT);
   KRotation&	FromQuarternion(const double& s,const double& q1,const double& q2,const double& q3);
   KRotation&	FromQuarternion(const KVector& vQ){ return FromQuarternion(vQ[0],vQ[1],vQ[2],vQ[3]); }
   void     	Rodrigues(double& a,double& b,double& c);
   void     	Euler(double& a,double& b,double& c,const int& nT);
   void     	Quarternion(double& s,double& q1,double& q2,double& q3);
   void     	AxisRotation(KVector& vAxis,double& dPhi);
   void     	Angle(int nCol,double& a,double& b,double& c,int nType);

   KVector  	Rodrigues();
   KVector  	Euler(const int& nT=_DEG);
   KVector  	Quarternion();
   void     	Quarternion(KVector& vQ);

   KRotation&   Orthogonalized(); //find the nearest orthogonal rotation matrix from itself
   KRotation	Orthogonalize();
   bool			IsRightHand();

   KRotation&  operator =(const KMatrix&);
   KRotation   operator *(const KRotation&);
   KVector	   operator *(const KPoint3D&);
   KMatrix     operator *(const KMatrix&);
};

///////////////////////////////////////////////////////////
//
// class KHomogeneous
//
class KHomogeneous : public KMatrix //tag : h
{

public:
	KHomogeneous() : KMatrix(4,4,_IDENTITY){ }
	KHomogeneous(const KHomogeneous& hT) : KMatrix(4,4,hT.Address()){ }
	KHomogeneous(const KRotation& rR,const KVector& vT) : KMatrix(4,4,_IDENTITY){ Place(0,0,rR); Place(0,3,vT); }
	KHomogeneous(const KMatrix& mT) : KMatrix(4,4,mT.Address()){ }
	KHomogeneous(const KVector& vEulerTranslation) : KMatrix(4,4,_IDENTITY) {  Create(vEulerTranslation); }

	void 		 Create(const KVector& vET){
					Place(0,0,KRotation(vET[0],vET[1],vET[2],_RAD));
					Place(0,3,vET.Cut(3,5));
				 }


	KHomogeneous Iv() const;
	KRotation    R()  const  { return KRotation(this->To(2,2)); }
	KVector 	 t()  const  { return KVector(_ppA[0][3],_ppA[1][3],_ppA[2][3]); }
	KVector		 EulerTranslation(){ return KRotation(this->To(2,2)).Euler(_RAD).Tailed(this->Column(3).To(2)); }

	KHomogeneous& operator =(const KHomogeneous&);
	KHomogeneous  operator ~() const;
};


////////////////////////////////////////////////////////////
//
// class KQuaternion

class KQuaternion : public KVector //tag:q
{

public:
	KQuaternion() : KVector(4){ }
	KQuaternion(const KVector& vAxis,const double& dTheta) : KVector(4){ Create(vAxis,dTheta); }
	virtual ~KQuaternion(){ }

	void            Create(const KVector& vAxis,const double& dTheta);



	KRotation       Rotation();
	void            AxisRotation(KVector& vAxis,double& dTheta);

    KQuaternion&    operator =(const KVector&);
    KQuaternion     operator *(const KQuaternion&);
    KQuaternion     operator ~() const;
};



////////////////////////////////////////////////////////////
//
// class KEdge

typedef struct tagKEDGEPIXEL{
	unsigned short   u;
	unsigned short   v;
	unsigned short   wAng;//0-360
	unsigned short   wDir;//0,1,2,3
	double  		 dMag;
}KEDGEPIXEL;

class KEdge : public KStack<KEDGEPIXEL>
{
   KMatrix			 _mKernelX, _mKernelY;  //convolution mask
   KImageDouble      _idGradX, _idGradY;
   KImageDouble      _idMag,_idBuf;         //buffer for edge gradients and magnitudes
   KImageWord		 _iwAng;                //0~360
   KImageGray        _igDir;                //0~3

   int              _nHalf, _nMaskLength;  //dimension of convolution mask
   int              _nWidth, _nHeight;     //image size
   KRect			_rcArea;
   double           _dSigma;               //edge stdev.

   //intermediates
	KStack<KEDGEPIXEL> _skTmp;
	KMath              _oMath;
	unsigned int	   _dwpSQR[111];       //store square of (10*index) for fast calculation

public:
	KEdge(){ }
	KEdge(double dSigma,int nLength=0,int nCapacity=2000){ Create(dSigma,nLength,nCapacity); }
	~KEdge(){}
	void         Create(double dSigma,int nLength=0,int nCapacity=2000);
    virtual void Sort(int nType);

//operations
public:
	void    Canny(double dLow,double dHigh,const KImageGray& igIn);
	void    Canny(double dLow,double dHigh,const KImageGray& igIn,  KImageGray& igOut);
	void    Canny(double dLow,double dHigh,const KImageDouble& idIn,KImageGray& igOut);

	void 	Canny(double dLow,double dHigh,const KRect& rcFrom,const KRect& rcTo,const KImageGray& igIn);

	void    Canny(double dLow,double dHigh,const KRect& rcWin,const KImageGray& igIn);
	void    Canny(double dLow,double dHigh,const KRect& rcWin,const KImageColor& icIn);
	void    Canny(double dLow,double dHigh,const KRect& rcWin,const KImageColor24& icIn);

	void    Gradient(const KRect& rcRegion,const KImageGray& igIn);
	void    Gradient(const KRect& rcRegion,const KImageDouble& afIn);
	void    Gradient(const KImageGray& igIn, KImageGray& igOut);
	void    Gradient(const KImageDouble& idIn);
	void	DT(const double& dBW,KImageWord& iwDist,KImageWord& iwDir);
//getting
public:
	int             Width()  const { return _nWidth; }
	int             Height() const { return _nHeight; }
	int             Half()   const { return _nHalf; }

	KImageDouble&   GradX(){ return _idGradX; }
	KImageDouble&   GradY(){ return _idGradY; }
	KMatrix&   		KernelX(){ return _mKernelX; }
	KMatrix&   		KernelY(){ return _mKernelY; }
};
//---------------------------------------------------------------------------


////////////////////////////////////////////////////////////
//
// class KCorner

typedef struct tagKCORNERPIXEL{
    unsigned short   u;
    unsigned short   v;
    double  		      dR;
}KCORNERPIXEL;

class KCorner : public KStack<KCORNERPIXEL>
{
   KMatrix			   _mKernelX, _mKernelY;  //convolution mask
   KImageDouble     _idGradXGradX, _idGradYGradY, _idGradXGradY ;
   KImageDouble     _idR;
   int                     _nHalf, _nMaskLength;  //dimension of convolution mask

   int                     _nBlockSize, _nHalfBlock;
   KMatrix              _mBlockWeight;


   //intermediates
    KStack<KCORNERPIXEL> _skTmp;

public:
    KCorner( ){ }
    KCorner(const double& dSigma_a, const int& nBlockSize, const int& nCapacity=2000){ Create(dSigma_a,nBlockSize,nCapacity); }
    virtual ~KCorner(){ }

    void                   Create(const double& dSigma_a, const int& nBlockSize, const int& nCapacity=2000);

//operations
public:
    void                   HarrisCorner(const double& dThresh, const KImageGray& igIn);

//getting
public:    
    KImageDouble&   GradXGradX(){ return _idGradXGradX; }
    KImageDouble&   GradXGradY(){ return _idGradXGradY; }
    KImageDouble&   GradYGradY(){ return _idGradYGradY; }

};
//---------------------------------------------------------------------------


class KGaussian   //tag : g
{
protected:
    double      	_dMean;
    double			_dSigma;

	int				_nNum;	
	double      	_dVar,_dVar2;	
	int				_nIdx;
	float*      	_fpRandom;
	KRandom*    	_opRandom;
	double          _dRandom;
	double          _dConst;

public:
	KGaussian();
	KGaussian(const double& dMean,const double& dVar){ Create(dMean,dVar); }
	virtual ~KGaussian();

public:
	void		Create(const double& dMean,const double& dVar);
	double		Pdf(const double& dX);
	double      Exp(const double& dX);
	double		Pdf(const double& dX,const double& dMean,const double& dVar);
	double	    MahaDistance(const double& dX){ return _SQR(_dMean-dX)/_dVar; }
	double&     Mean(){ return _dMean; }
	double&     Var(){  return _dVar; }
	int&        RandomSize(){ return _nNum; }
	double&		Generate( );
	double&		Generate(const double& dMean,const double& dSigma);

	bool		OnRandom(int nNum=1000);
	void		OffRandom( );

    bool      Read(FILE* file);
    void      Write(FILE* file);
	void		WriteText(FILE* file);
	KGaussian&  operator = (const KGaussian& gIn);
};
//---------------------------------------------------------------------------

class KGaussianMulti  //tag : mg
{
    int         _nDim;		//size of dimension
    KVector     _vMean;
    KMatrix     _mCov;		//covariance matrix

	KMatrix	    _mLowCov;	    //the lower matrix from Cholesky decomposition of oSigma
	KGaussian*	_gpGaussians;	//the list of single gaussian distibution
	KVector     _vRandom;       //to be used in generating random vertor
							    //drawn from this distribution
public:
	double		_dConst;
	double      _dConstNormal;
	KMatrix	    _mIvCov;		//inverse of the covariance matrix

public:
	KGaussianMulti();
	KGaussianMulti(const KVector& vMean, const KMatrix& mCov);
	KGaussianMulti(int nDim);
	virtual ~KGaussianMulti(){	if(_gpGaussians) delete[] _gpGaussians; }

	bool        Create(int nDim);    
	bool        Create(const KVector& vMean, const KMatrix& mCov);
    void		Release(){ _vMean.Release(); _mCov.Release();  if(_gpGaussians) delete[] _gpGaussians; }

    bool		Read(FILE*);
	bool        Read(char* szFile);
    void		Write(FILE*);
    void		WriteText(FILE*);
	double      Pdf(const KVector& vX);
	double      PdfNormal(const KVector& vX);
	double      Pdf(const double& d1,const double& d2); //2-d case    
	double      LogPdf(const double& d1,const double& d2); //2-d case
	double      Exp(const KVector& vX);
	double      LogPdf(const KVector& vX);
    double      LogExp(const KVector& vX);
    double	    Mahalanobis(const KVector& vX);

	static double	Pdf(const KVector& vX,const KVector& vMean,const KMatrix& mCov);
	static double	LogPdf(const KVector& vX,const KVector& vMean,const KMatrix& mCov);
	static double	Mahalanobis(const KVector& vX,const KVector& vMean,const KMatrix& mCov);
	static KVector  Kernel_1D(const double& dSigma,const int& nSize=0);
	static KVector  Kernel_Derivative(const double& dSigma,const int& nSize=0);    
	static KMatrix  Kernel_2D(const double& dSigma,const int& nSize=0);

public:
    KMatrix&        Cov() { return  _mCov; }
    KVector&        Mean() { return _vMean; }
    int             Dim() { return _nDim;  }
    bool            Enabled(){ return (bool)_mCov.Pointer(); }
    void            Update(){ Create(_vMean,_mCov); }

public:
    bool            OnRandom(int nNum = 1000);
    void            OffRandom();

	KVector&	    Generate();
	KVector&	    Generate(KMatrix& mLowCov);

	KGaussianMulti& operator = (const KGaussianMulti& gIn);
};

class KGaussianMixture //tag: gm
{
    char            _szID[200];
    int             _nNum;      //number of Gaussians
    KVector         _vWeight;   //weight of each Gaussian
    KGaussianMulti*	_gpMulti;   //pointers of Gaussian distributions
    KGaussian*      _gpSingle;  //pointers of Gaussian distributions
    int             _nType;     //_SINGLE: single-variate gaussian, _MULTI: multivariate gaussian

public:   
    KGaussianMixture(){ _gpMulti = 0; _gpSingle = 0; }
	//외부에서 가우시안 정보를 가지고 초기화 할 경우
	KGaussianMixture(const KGaussianMixture& oGmx);
	KGaussianMixture(const KVector& vWeight, KGaussianMulti* gpDtb);
    KGaussianMixture(const KVector& vWeight, KGaussian* gpDtb);
    virtual ~KGaussianMixture(){ if(_gpMulti) delete[] _gpMulti; if(_gpSingle) delete[] _gpSingle; }

    void        Create(const KVector& vWeight, KGaussianMulti* gpDtb);
    void        Create(const KVector& vWeight, KGaussian* gpDtb);
    bool        Load(FILE* fp);
    bool        Load(const char* szFile);

    //입력데이터로부터 학습할 경우에 사용
    double      Learning(int nNum,KMatrix& mSample);//each column is a feature vector
    double      Learning(int nNum,KVector& vSample);


	//공통
    void        Save(const char* szFile);
    void        SaveText(const char* szFile);
    void        Save(FILE* fp);

    double      Pdf(const double&);
    double      Pdf(const KVector&);
    double      PdfNormal(const KVector&);
    double      Pdf(const double& a,const double& b);
    double      LogPdf(const KVector&);
    double      LogPdf(const double&);

	//get & set
    void            ID(const char* szName){ strcpy(_szID,szName); }
    char*           ID() { return _szID; }
    int             Count() const  { return _nNum; }
    bool            Enabled(){ return (_gpMulti || _gpSingle); }
    int             Type()  const { return _nType; }
    KGaussianMulti* Gaussian(int i){ return &_gpMulti[i]; }
    KGaussianMulti* Gaussians(){ return _gpMulti; }
	KVector&        Weight(){ return _vWeight; }

	KGaussianMixture& operator = (const KGaussianMixture&);

protected:
	bool            InitLearning(int nNum,KMatrix& mSample);
    bool            InitLearning(int nNum,KVector& vSample);

};

/////////////////////////////////////////////////////////////////////////////////


#include <windows.h>

class WStopWatch
{
private:
	LARGE_INTEGER       _iFreq;
	LARGE_INTEGER		_iStart,_iEnd;

public:
	WStopWatch(){ }
	virtual ~WStopWatch(){ }

	bool   Init(){  return QueryPerformanceFrequency(&_iFreq); }
	void   Start(){	QueryPerformanceCounter(&_iStart);  }
	void   End(){	QueryPerformanceCounter(&_iEnd);    }
	double ElapsedTime(){ return 1000.0*((double)(_iEnd.QuadPart - 
						  _iStart.QuadPart) / (double)(_iFreq.QuadPart));}
};
/////////////////////////////////////////////////////////////////////////////////

#define     _EVENT_ERROR     -1
#define     _EVENT_NOWAIT     1
#define     _EVENT_TIMEOUT    2
#define     _EVENT_NOTIFIED   3

#include <process.h>

class WEvent
{
	long				  _lWaitCount;
	HANDLE      _hEvent;
	DWORD       _dwRet;

public:
	WEvent();
	virtual ~WEvent(){ ::CloseHandle(_hEvent); }

public:
	int         Wait(DWORD nMsec=INFINITE);
	bool       Notify(bool bNotifyOnWait){ return ( bNotifyOnWait ? (_lWaitCount ? ::SetEvent(_hEvent):false) : ::SetEvent(_hEvent)); }
	bool       Locked(){ return (_lWaitCount ? true:false); }
};

class WEventMulti
{
	long				_lWaitCount;
	int				_nNum;
	HANDLE*	_hpEvents;
	bool				_bWaitAll;
	DWORD		_dwMsec;
	DWORD      _dwRet;

public:
	WEventMulti(){ _hpEvents = 0; }
	WEventMulti(int nNum,bool bWaitAll=true,DWORD dwMsec=1000){ _hpEvents = 0; Create(nNum,bWaitAll,dwMsec); }
	virtual ~WEventMulti();

	void		Create(int nNum,bool bWaitAll,DWORD dwMsec);

public:
	int 		Wait();
	int			WaitEx(bool bWaitAll,DWORD dwMsec);
	bool        Locked(){ return (_lWaitCount ? true:false); }
	HANDLE		Event(int nID){ return _hpEvents[nID]; }
	void		Notify(int nID){ ::SetEvent(_hpEvents[nID]); }
};
/////////////////////////////////////////////////////////////////////////////////

class WCriticalSection
{
public:
	WCriticalSection();
	virtual ~WCriticalSection();

protected:
	_RTL_CRITICAL_SECTION _csSync;

public:
	void        Lock() { ::EnterCriticalSection(&_csSync); }
	void        Unlock() { ::LeaveCriticalSection(&_csSync); }
	int         LockCount() { return _csSync.LockCount; }
};
/////////////////////////////////////////////////////////////////////////////////

class WThread
{
protected:
    HANDLE         _hThread;
    unsigned int    _uiThreadID;
    int                    _nCountSuspended;
    bool                 _bTerminated;
    int                    _nWaitTerminate;
    unsigned int    _dwWaitExecute;
    unsigned int    _dwPriority;       //thread priority
    WEvent           _eTerminate;      //event for thread termination
    WEvent           _eExecute;        //event for performing 'Execute()'
    bool                 _bExecuteNotify;  //whether the thread use '_eExecute', that is, execution dependson the call of Notify(..)

public:
	WThread(bool bExecuteNotify,unsigned int dwPriority=THREAD_PRIORITY_NORMAL,DWORD dwWaitExecute=1000);
	virtual ~WThread();

public:
					//create and start the thread.
					//call this function for first start of the thread and its restart
					//after terminating the thread.
	void    		Start();
					//terminate the thread
	void    		Terminate();
					//call this function for restart of the thread after its suspending
	int     		Resume();
					//suspend the thread
	int     		Suspend();

					//check if the thread is suspended
    bool         Suspended(){ return (_nCountSuspended ? true:false); }
					//check if the thread is terminated
	bool    		Terminated(){ return _bTerminated; }
					//return true if the thread is waiting for executing notification
    bool         ExecuteLocked(){ return _eExecute.Locked(); }

					//this function is for execution notification that is a signal to perform 'Exucute()'.
					//this function is valid when '_bExecuteNotify' is set to true.
    bool         Notify(bool bNotifyOnWait=true,void* p1=0,void* p2=0,void* p3=0)
					{
						if(_nCountSuspended==0 && !_bTerminated)
						{
							if(_eExecute.Locked())
							{
                                if(p1) TransferData(p1,p2,p3);
								return _eExecute.Notify(bNotifyOnWait);
							}
						}
						return false;
					}

					//priority
	bool			Priority(const unsigned int& dwPriority){ _dwPriority = dwPriority;	return ::SetThreadPriority(_hThread,_dwPriority); }
    int			Priority(){ return ::GetThreadPriority(_hThread); }

private:
	static unsigned __stdcall ThreadMain(void* pContext);

protected:
    virtual void         Execute() = 0;
	virtual void    		TransferData(void* p1,void* p2,void* p3){ };
};

/////////////////////////////////////////////////////////////////////////////////


enum BITS_NUMT {BITS_1, BITS_8, BITS_24, BITS_32};

typedef struct tagMOVIEINFO{
    char          szID[20];
	int             nFrameRate;//[frm/s]
	int             nLength;
	int             nDepth;    //bits per pixel
	int             nWidth;
	int             nHeight;

}KMOVIEINFO;

class KMovie : public KPtrList<void*> //tag : kmv

{
	KMOVIEINFO  _oInfo;

public:
	KMovie(){  };
	KMovie(const int& nDepth,const int& nWidth,const int& nHeight,const int& nSize=500,const char* szID=0){ Create(nDepth,nWidth,nHeight,nSize,szID); }
	virtual ~KMovie(){ RemoveAll(); }

    void			   Create(const int& nDepth,const int& nWidth,const int& nHeight,const int& nSize=500,const char* szID=0);
	bool            Load(const KString& asFile);
	bool            Save(const KString& asFile);
    char*          ID(){ return _oInfo.szID; }
	void            SetID(char* szID);
    int              Width(){  return _oInfo.nWidth; }
    int              Height(){ return _oInfo.nHeight;}
    int			   Depth(){  return _oInfo.nDepth; }
    int              Add(void*);
	bool            IsEmpty(){ return (Count()==0 ? true:false); }
	void            RemoveAll();
	bool            AssignTo(int nFrame,KImageGray& igImg);
	bool            AssignTo(int nFrame,KImageColor& icImg);
	void            FrameRate(int nFrmRate){ _oInfo.nFrameRate = nFrmRate; }
    int              FrameRate(){ return _oInfo.nFrameRate; }

    void*                       Image(int i){   return ( (i>-1 && i<KPtrList<void*>::Count()) ? (*this)[i]:0 ); }
	KMOVIEINFO      MovieInfo() const { return _oInfo; }
    KMOVIEINFO&    MovieInfo(){ return _oInfo; }
};
/////////////////////////////////////////////////////////////////////////////////


#define  _OPTIMA_GOLD     1.618034
#define  _OPTIMA_CGOLD    0.3819660
#define  _OPTIMA_GLIMIT   100
#define  _OPTIMA_TINY     1.0e-20
#define  _OPTIMA_ZEPS     1.0e-10
#define  _OPTIMA_SHIFT(a,b,c,d) (a)=(b); (b)=(c);(c)=(d);

class KOptima
{
protected:
	int         _nMaxItr, _nMaxItr2;
	KVector    	_vP;          //starting point
	KVector    	_vDir; //direction of minimization
	KMatrix    	_mDir;

	KVector     _vHistoryErf;

public:
   KOptima(int nMaxItr=15,int nMaxItr2=30){ _nMaxItr = nMaxItr; _nMaxItr2 = nMaxItr2; }
   virtual ~KOptima(){ };

public:
	bool		Powell(KVector& vP,double dTol,int nItr=0){ return ExecuteWithoutGradients(vP,dTol,nItr); }
	bool		ExecuteWithoutGradients(KVector& vP,double dTol,int nItr=0); //Powell method
	bool		ExecuteWithGradients(KVector& vP,double dTol,int nItr=0);    //Fletcher-Reeves and Polak-Ribiere

   KVector& HistoryErf(){ return _vHistoryErf; }

protected:
   virtual double   Erf(const KVector& vX) = 0;
   virtual void		OnIteration(){ }
   virtual KVector&	ErfD(const KVector& vX) { return _vDir; }

   virtual void		OnUpdate(KVector& vP){ }

   //minimization along a line
   double           LineMin();
   double			LineMinD();
   //from 10.1 of "Numerical Recipes in C"
   void             GoldenSection(double& dA,double& dB,double& dC,double& dFa,double& dFb,double& dFc);
   //from 10.2 of "Numerical Recipes in C"
   double           Brent(double dA,double dB,double dC,double dTol,double& dXmin);
   double           BrentD(double dA,double dB,double dC,double dTol,double& dXmin);
   //one dimensional function to be minimized
   double           Fun1D(double);
   double           DFun1D(double);

};
/////////////////////////////////////////////////////////////////////////////////


template< class T > KArray<T>::KArray( )
{
	_ppA   = 0;
	_nRow  = _nCol = 0;
	_nMode = _ALLOC;
}

template< class T > KArray<T>::KArray(const int& nRow, const int& nCol)
{
	_ppA   = 0;
	_nMode = _ALLOC;
	_nRow  = _nCol = 0;

	Create(nRow,nCol);
}

template< class T > KArray<T>::KArray(const int& nRow, const int& nCol,T* pINIT,int nMode)
{
	_ppA   = 0;
	_nMode = _ALLOC;
	_nRow  = _nCol = 0;

	Create(nRow,nCol,pINIT,nMode);
}

template< class T > KArray<T>::~KArray()
{
	if(_ppA){
		if(_nMode == _ALLOC)
			delete[] _ppA[0];
		delete[] _ppA;
	}
}

template< class T > void KArray<T>::Release( )
{
	if(_ppA){
		if(_nMode == _ALLOC)
			delete[] _ppA[0];
		delete[] _ppA;
		_ppA = 0;
		_nRow = _nCol = 0;
	}
}

template< class T > void KArray<T>::Create(const int& nRow, const int& nCol,T* pINIT,int nMode)
{
#ifdef _DEBUG
	assert(!(pINIT==0 || nRow==0 || nCol==0));
#endif

	//delete the allocated memory
	if(_ppA)
	{
		if(_nMode == _ALLOC){
			if(_nMode != nMode || (_nRow != nRow || _nCol != nCol)){ delete[] _ppA[0]; delete[] _ppA; _ppA = 0; }
			else{  memcpy(_ppA[0],pINIT,_nSize*sizeof(T)); return; }
		}
		else{ //_LOCK
			if(_nMode != nMode || (_nRow != nRow || _nCol != nCol)){ delete[] _ppA; _ppA = 0; }
			else{
				_ppA[0] = pINIT;
				for(int i=1; i<nRow; i++)
					_ppA[i] = _ppA[i-1] + nCol;
				return;
			}
		}
	}

	//set
	_nMode  = nMode;
	_nRow   = nRow;
	_nCol   = nCol;
	_nSize  = (unsigned int)(nRow)*(unsigned int)(nCol);
	_ppA    = new T* [nRow];

	if(nMode == _ALLOC)
	{
		_ppA[0] = new T[_nSize];
		memcpy(_ppA[0],pINIT,_nSize*sizeof(T));
	}
	else
		_ppA[0] = pINIT;

	for(int i=1,ic=nRow-1; ic; ic--, i++)
		_ppA[i] = _ppA[i-1] + nCol;
}

template< class T > void KArray<T>::Create(const int& nRow, const int& nCol)
{
#ifdef _DEBUG
	assert(!(nRow==0 || nCol==0));
#endif

	//delete the allocated memory
	if(_ppA){
		if(_nMode==_ALLOC && (_nRow != nRow || _nCol != nCol))
		{
			delete[] _ppA[0];
			delete[] _ppA; _ppA = 0;
		}
		else if(_nMode==_LOCK && (_nRow != nRow || _nCol != nCol))
		{
            delete[] _ppA;
            _ppA = 0;
		}
		else{
			memset(_ppA[0],0,_nSize*sizeof(T));
			return;
		}
	}

	//memory alloc.
	_nMode  = _ALLOC;
	_nRow	= nRow;
	_nCol   = nCol;
	_nSize  = (unsigned int)(nRow)*(unsigned int)(nCol);

	_ppA    = new T* [nRow];
	_ppA[0] = new T[_nSize];
	memset(_ppA[0],0,_nSize*sizeof(T));

	//set pointers
	for(int i=1,ic=nRow-1; ic; ic--, i++)
		_ppA[i] = _ppA[i-1] + nCol;
}

template<class T> void KArray<T>::Fliped()
{
	T* pTmp = new T[_nCol];

	int  nTo 	= _nRow/2;
	int  nSize	= sizeof(T)*_nCol;

	for(int i=0,ii=_nRow-1; i<nTo; i++,ii--)
	{
		memcpy(pTmp,_ppA[ii],nSize);
		memcpy(_ppA[ii],_ppA[i],nSize);
		memcpy(_ppA[i],pTmp,nSize);
	}
	delete[] pTmp;

}

template<class T> T* KArray<T>::operator [] (const int& i) const
{
	return _ppA[i];
}

template<class T> KArray<T>& KArray<T>::operator = ( const KArray<T>& 	arFrom)
{
	if(arFrom._ppA)
	{
        if(_ppA == 0 || _nRow != arFrom._nRow || _nCol != arFrom._nCol)
			Create(arFrom._nRow,arFrom._nCol,arFrom._ppA[0],_ALLOC);
		else
			memcpy(_ppA[0],arFrom._ppA[0],_nSize*sizeof(T));
	}

	return *this;
}

template<class T> KArray<T>& KArray<T>::operator =  ( const T& 	t)
{
#ifdef _DEBUG
	assert(_ppA != 0);
#endif

	//copy
    for(int i=0,ic=_nRow; ic; ic--, i++)
        for(int j=0,jc=_nCol; jc; jc--, j++)
            _ppA[i][j] = t;

	return *this;
}

template< class T > void KArrayObject<T>::Create(const int& nRow, const int& nCol)
{
#ifdef _DEBUG
	assert(!(nRow==0 || nCol==0));
#endif

	//delete the allocated memory
	if(_ppA)
	{
		if(_nRow != nRow || _nCol != nCol)
		{
			delete[] _ppA[0];
			delete[] _ppA;
			_ppA = 0;
		}
		else
		{
        //	for(int ii=_nSize,i=0; ii; ii--,i++)
        //		_ppA[0][i].Release();
			return;
		}
	}

	//set
	_nRow   = nRow;
	_nCol   = nCol;
	_nSize  = nRow*nCol;
	_ppA    = new T* [nRow];

	_ppA[0] = new T[_nSize];
	for(int i=1,ic=nRow-1; ic; ic--, i++)
		_ppA[i] = _ppA[i-1] + nCol;
}
					 
template< class T > void KArrayObject<T>::Create(const KArrayObject<T>& arFrom)
{
#ifdef _DEBUG
	assert(arFrom.Pointer());
#endif
    
	Create(arFrom.Row(), arFrom.Col());

    for(int i=0, ic=Size(); ic;  i++, ic--)
		_ppA[0][i] = arFrom._ppA[0][i];
}

template<class T> T* KArrayObject<T>::operator [] (const int& i) const
{
	return _ppA[i];
}

template<class T> KArrayObject<T>& KArrayObject<T>::operator = ( const KArrayObject<T>&  arFrom)
{
#ifdef _DEBUG
	assert(arFrom.Pointer());
#endif

	Create(arFrom.Row(), arFrom.Col());

    for(int i=0, ic=Size(); ic;  i++, ic--)
        _ppA[0][i] = arFrom._ppA[0][i];

	return *this;
}
///////////////////////////////////////////////////////////////////////////////////////////


template< class T > KList<T>::KList(const unsigned int& uiCapacity)
{
#ifdef _DEBUG
	assert(uiCapacity>0);
#endif

	_pItems      = 0;
	Create(uiCapacity);
}

template< class T > void KList<T>::Create(const unsigned int& uiCapacity)
{
	//clear
	if(_pItems){
		RemoveAll();
		delete[] _pItems;
	}

	//set
	_uiCapacity = uiCapacity;
	_pItems     = new T[uiCapacity];

	//init.
	_uiCount = 0;
}

template< class T > void KList<T>::RemoveAll()
{
	if(_uiCount)
		_uiCount = 0;
}

template< class T > unsigned int KList<T>::RemoveAt(const unsigned int& uiID)
{
#ifdef _DEBUG
	assert(uiID >= 0 && uiID < _uiCount);
#endif

	//update the list
	for(unsigned int i=uiID; i<_uiCount-1; i++){
		_pItems[i] = _pItems[i+1];
	}

	//count
	return --_uiCount;
}

template< class T > void KList<T>::Swap(const unsigned int& n1,const unsigned int& n2)
{
#ifdef _DEBUG
	assert(!(n1<0 || n2<0 || n1>=_uiCount || n2>=_uiCount));
#endif

	T pOld = _pItems[n1];
	_pItems[n1] = _pItems[n2];
	_pItems[n2] = pOld;
}

template< class T > unsigned int KList<T>::Find(const T& p)
{
	//update the list
    for(unsigned int i=0; i<_uiCount; i++)
		if(_pItems[i] == p)
			return i;
	return -1;
}


template< class T > unsigned int KList<T>::Add(T t)
{
#ifdef _DEBUG
	assert(_pItems != 0);
#endif

	if(_uiCount == _uiCapacity)
	{
		//alloc. a new memory block
		_uiCapacity += (int)(_uiCapacity*0.3);
		T* pNew = new T[_uiCapacity];

		//copy the old block to the new one
		for(unsigned int i=0; i<_uiCount; i++)
			pNew[i] = _pItems[i];

		//delete the old block
		delete[] _pItems;

		//set the item pointer
		_pItems = pNew;
	}

	//add
	_pItems[_uiCount] = t;

	return ++_uiCount;
}

template< class T > unsigned int KList<T>::Add(KList<T>& lAdd)
{
#ifdef _DEBUG
	assert(_pItems);
#endif

	unsigned int nAdd = lAdd.Count();

	if(_uiCount + nAdd >= _uiCapacity)
	{
		//alloc. a new memory block
		T* pNew = new T[(_uiCapacity += (_uiCount + (int)(nAdd*1.3)))];

		//copy the old block to the new one
		for(unsigned int i=0,ii=_uiCount; ii; i++,ii--)
			pNew[i] = _pItems[i];

		//delete the old block
		delete[] _pItems;

		//set the item pointer
		_pItems = pNew;
	}

	//add
    for(unsigned int i=_uiCount, j=0, ii=nAdd; ii; i++,j++,ii--)
		_pItems[i] = lAdd._pItems[j];
	_uiCount += nAdd;


	return _uiCount;
}

template< class T > KList<T>& KList<T>::Reversed( )
{
    //reverse copy
    T tmp;
    for(unsigned int i=0,ii=_uiCount-1; i<_uiCount/2; i++,ii--)
    {
        tmp = _pItems[i];
        _pItems[i]  = _pItems[ii];
        _pItems[ii] = tmp;
    }

    return *this;
}

//---------------------------------------------------------------------------
template< class T > KList<T>& KList<T>::operator = ( const KList<T>& oList)
{
	RemoveAll();

	for(unsigned int i=0; i<oList.Count(); i++)
		Add(oList[i]);

	return *this;
}
//---------------------------------------------------------------------------

template< class T > KPtrList<T>::KPtrList(const unsigned int& uiCapacity,bool bOwnership,bool bArray)
{
#ifdef _DEBUG
	assert(uiCapacity>0);
#endif
	_pItems  = 0;

	Create(uiCapacity,bOwnership,bArray);
}

template< class T > void KPtrList<T>::Create(const unsigned int& uiCapacity,bool bOwnership,bool bArray)
{
	//clear
	if(_pItems){
		RemoveAll();
		delete[] _pItems;
	}

	//flag
	_bOwnership = bOwnership;
	_bArray     = bArray;

	//alloc.
	_uiCapacity  = uiCapacity;
	_pItems      = new T[uiCapacity];

	//init.
	memset(_pItems,0,sizeof(T)*uiCapacity);
	_uiCount = 0;
}


template< class T > void KPtrList<T>::RemoveAll()
{
	if(_uiCount){
		//delete items
		if(_bOwnership){
			if(_bArray){
				for(int i=0; i<_uiCount; i++)
					delete[] _pItems[i];
			}
			else{
				for(int i=0; i<_uiCount; i++)
					delete _pItems[i];
			}
		}
		//init.
		memset(_pItems,0,sizeof(T)*_uiCount);
		_uiCount = 0;
	}
}

template< class T > void KPtrList<T>::RemoveAt(const unsigned int& uiID)
{
#ifdef _DEBUG
	assert(!(_uiCount == 0 || uiID < 0 || uiID >= _uiCount));
#endif
	//delet the item
	if(_bOwnership)
	{
		if(_bArray)	delete []_pItems[uiID];
		else		delete _pItems[uiID];
	}

	//update the list
	for(int i=uiID; i<_uiCount-1; i++)
	{
		_pItems[i] = _pItems[i+1];
	}
	_pItems[_uiCount-1] = 0;

	//count
	_uiCount --;
}

template< class T > void KPtrList<T>::Remove(const unsigned int& nFrom,const unsigned int& nTo)
{
#ifdef _DEBUG
	assert(!(_uiCount == 0 || nFrom < 0 || nTo >= _uiCount || nFrom > nTo));
#endif

	//delet the item
	unsigned int i,ic,j;
	unsigned int nNumDeleted = nTo - nFrom + 1;
	if(_bOwnership)
	{
		if(_bArray)
			for(i=nFrom,ic=nNumDeleted; ic; ic--,i++)
				delete[] _pItems[i];
		else
			for(i=nFrom,ic=nNumDeleted; ic; ic--,i++)
				delete _pItems[i];

	}

	//update the list
	for(i=nFrom,j=nTo+1,ic=nNumDeleted; ic; ic--, i++,j++)
	{
		_pItems[i] = _pItems[j];
	}
	_pItems[(_uiCount -= nNumDeleted)] = 0;
}


template< class T > int KPtrList<T>::Find(const T& p)
{
	//update the list
    for(unsigned int i=0; i<_uiCount; i++)
		if(_pItems[i] == p)
			return i;

	return -1;
}

template< class T > void KPtrList<T>::Remove(const T& p)
{
	//update the list
	for(int i=0; i<_uiCount; i++)
	{
		if(_pItems[i] == p)
		{
			if(_bOwnership)
			{
				if(_bArray)	delete []_pItems[i];
				else		delete _pItems[i];
			}

			for(int j=i; j<_uiCount-1; j++)
				_pItems[j] = _pItems[j+1];
			_pItems[_uiCount-1] = 0;

			break;
		}
	}
	//count
	_uiCount --;
}

template< class T > void KPtrList<T>::Swap(const unsigned int& n1,const unsigned int& n2)
{
#ifdef _DEBUG
	assert(!(n1<0 || n2<0 || n1>=_uiCount || n2>=_uiCount));
#endif

	T pOld = _pItems[n1];
	_pItems[n1] = _pItems[n2];
	_pItems[n2] = pOld;
}

template< class T > unsigned int KPtrList<T>::Add(T t)
{
	if(_uiCount == _uiCapacity){
		//alloc. a new memory block
		T* pNew = new T[(_uiCapacity += (int)(_uiCapacity*0.3))];
		//copy the old block to the new one
		memcpy(pNew,_pItems,sizeof(T)*_uiCount);
		//delete the old block
		delete[] _pItems;
		//set the item pointer
		_pItems = pNew;
	}

	//add
	if(t)
		_pItems[_uiCount++] = t;

	return _uiCount;
}
//---------------------------------------------------------------------------


template< class T > unsigned int KPtrList<T>::Add(KPtrList<T>* lpList)

{
#ifdef _DEBUG
	assert(lpList->_bOwnership == _bOwnership);
#endif

	if(lpList == 0 || lpList->Count() == 0)
		return _uiCount;

	if(_uiCount + lpList->Count() > _uiCapacity)
	{
		//alloc. a new memory block
		T* pNew = new T[(_uiCapacity += (_uiCount + (int)(lpList->Count()*1.3)))];
		memcpy(pNew,_pItems,sizeof(T)*_uiCount);
		//delete the old block
		delete[] _pItems;
		//set the item pointer
		_pItems = pNew;
	}

	//add
	memcpy(&_pItems[_uiCount],lpList->_pItems,sizeof(T)*lpList->Count());
	_uiCount += lpList->Count();

	//remove the source list
	lpList->_bOwnership = false;

	return _uiCount;
}
//---------------------------------------------------------------------------


template< class T > KPtrList<T>& KPtrList<T>::operator = (KPtrList<T>& plList)
{
    if(plList._bOwnership == _bOwnership && _bOwnership)
        return *this;

	//clear the list
	RemoveAll();
	
	if(plList.Count() > _uiCapacity)
		Create(plList.Count()*1.5,_bOwnership,_bArray);

    if(plList.Count())
    {
        memcpy(_pItems,plList._pItems,sizeof(T)*plList.Count());
        _uiCount = plList.Count();
    }

	return *this;
}

template< class T > KStack<T>::~KStack()
{
	if(_pStack)
		delete[] _pStack;
}

template< class T > void KStack<T>::Create(const int& nSize)
{
	//reset the list
	if(_pStack)  delete[] _pStack;

	//alloc. memory
	_nCapacity = nSize;
	_pStack    = new T[nSize];

	//init.
	_nCount = 0;
	_nCur   = 0;
	_bLock  = false;
}

template< class T > void KStack<T>::RemoveAll()
{
	_nCount = 0;
	_nCur   = 0;
    _bLock  = false;
}

template< class T > void KStack<T>::Push(const T& t)
{
    if(_bLock) return;
    if(!(_nCur-_nCapacity)){
        //realloc. stack
        T* p = new T[_nCapacity += (int)(_nCapacity*0.3)];
		//copy the old stack to the new stack
        for(int i=0; i<_nCur; i++)   
			p[i] = _pStack[i];
        //delete the old stack
        delete[] _pStack;
        //store the new stack
        _pStack = p;
    }

    _pStack[_nCur++] = t;
    _nCount ++;
}

template< class T > int KStack<T>::Pop(T& out)
{
	if(_nCur){
        if(!_bLock) _nCount--;
        out = _pStack[-1+_nCur--];
		return _nCur;
    }
    if(_bLock)
        _nCur = _nCount;
    return -1;
}

template<class T> T KStack<T>::operator [](const int& nID)
{
    //assert(nID)
    return _pStack[nID];
}

template<class T> void KStack<T>::RemoveAt(const int& nID)
{
    for(int i=nID; i<_nCount-1; i++)
        _pStack[i] = _pStack[i+1];

    _nCount--;
    _nCur = (_nCur-1 >= nID ? _nCur-1:_nCur);
}

template< class T > void KQueue <T>::Create(const int& nCapacity)
{
	//reset the list
	RemoveAll();

	//alloc. memory
	_nCapacity = nCapacity;
	_pQueue    = new T[nCapacity];

	//init.
	_nOut 	  =  0;
	_nIn  	  =  0;
	_nRef 	  =  0;
	_nCount   =  0;	
}

template< class T > void KQueue<T>::RemoveAll()
{
	_nOut   =  0;
	_nIn    =  0;
	_nRef   =  0;
	_nCount =  0;
}

template< class T > void KQueue<T>::Reverse()
{
	T*	pTmp = new T[_nCapacity];
	T   oTmp;
	int nCnt = _nCount;

	for (int i = nCnt; i; i--)
	{
		this->Pop(oTmp);
		pTmp[i - 1] = oTmp;
	}
	delete[] _pQueue;

	_pQueue = pTmp;
	_nCount = nCnt;
	_nOut	= 0;
	_nIn	= nCnt;
	_nRef   = 0;
}


template< class T > int KQueue<T>::Push(const T& t, int* npIdx,T* pRemoved)
{
    if(_nCount == _nCapacity)
    {
        _nOut = (_nOut+1)%_nCapacity;
        if(pRemoved)
            *pRemoved = _pQueue[_nIn];
    }
	else
		_nCount ++;

	_pQueue[_nIn] = t;
    if(npIdx) *npIdx = _nIn;  //return the index of the pushed data

	_nIn 		  = (_nIn + 1)%_nCapacity;

	//Peek()의 초기화
	_nRef = 0;

	return _nCount;
}

template< class T > int KQueue<T>::Pop(T& out)
{
	if(_nCount)
	{
		out 	= _pQueue[_nOut];
		_nOut 	= (_nOut+1)%_nCapacity;
	}

	//Peek()의 초기화
	_nRef = 0;

	return (_nCount ? --_nCount : -1);
}

template< class T > int KQueue<T>::Remove(const T& out)
{
    for(int i=_nOut, ic=_nCount; ic; i++, ic-- )
        if( out == _pQueue[ i%_nCapacity ] )
        {
            for(int j = i, jc = ic-1; jc; j++, jc--)
                _pQueue[ j%_nCapacity ] = _pQueue[ (j+1)%_nCapacity ];

            _nCount --;
            _nIn --;
            return _nCount;
        }

    return 0;
}

template< class T > bool KQueue<T>::Peek(T& out)
{
	int nRef 	= (_nOut+_nRef)%_nCapacity;

	if(_nRef < _nCount)
	{
		out = _pQueue[nRef];
		_nRef ++;
		return true;
	}

	//Peek()의 초기화
	_nRef = 0;

	return false;
}

template< class T > bool KQueue<T>::Peek(int k,T& out)
{
	if(k < _nCount)
	{
		out = _pQueue[(_nOut + k)%_nCapacity];
		return true;
	}
	return false;
}

template< class T > void KQueue<T>::Swap(const int& n1,const int& n2)
{
#ifdef _DEBUG
	assert(!(n1<0 || n2<0 || n1>=_nCapacity || n2>=_nCapacity));
#endif

	T Old = _pQueue[n1];
	_pQueue[n1] = _pQueue[n2];
	_pQueue[n2] = Old;
}

template< class T > void KPtrQueue <T>::Create(const int& nCapacity, bool bOwnership, bool bFixedCapacity)
{
    //reset the list
    RemoveAll();

    //alloc. memory
    _nCapacity = nCapacity;    
    _pQueue    = new T[nCapacity];

    //init.
    _nOut 	  =  0;
    _nIn  	  =  0;
    _nRef 	  =  0;
    _nCount   =  0;
    _bFixedCapacity = bFixedCapacity;
    _bOwnership       = bOwnership;
}

template< class T > void KPtrQueue<T>::RemoveAll()
{
    _nOut   =  0;
    _nIn    =  0;
    _nRef   =  0;
    _nCount =  0;

    if(_pQueue && _bOwnership)
    {
        for(int i=_nOut, ii=_nCount; ii;  i = (i+1)%_nCapacity, ii--)
            delete _pQueue[i];
    }
}

template< class T > int KPtrQueue<T>::Remove(const T& out)
{
    for(int i=_nOut, ic=_nCount; ic; i++, ic-- )
        if( out == _pQueue[ i%_nCapacity ] )
        {
            if(_bOwnership)  delete _pQueue[ i%_nCapacity ];

            for(int j = i, jc = ic-1; jc; j++, jc--)
                _pQueue[ j%_nCapacity ] = _pQueue[ (j+1)%_nCapacity ];

            _nCount --;
            _nIn --;
            return _nCount;
        }

    return 0;
}


template< class T > int KPtrQueue<T>::Push(const T& t, int* npIdx)
{
    if(_nCount == _nCapacity)
    {
        if(_bFixedCapacity)
        {
            if(_bOwnership)
                delete _pQueue[_nOut];
            _nOut = (_nOut+1)%_nCapacity;
            _nCount --;
        }
        else
        {
            //realloc. stack
            T* p = new T[_nCapacity += (int)(_nCapacity*0.3)];
            //copy the old to the new
            for(int i=0; i<_nCount; i++)
                p[i] = _pQueue[i];

            //delete the old queue
            delete[] _pQueue;

            //store the new queue
            _pQueue = p;            

            _nIn = (_nIn+_nCapacity-1)%_nCapacity;
        }
    }

     _nCount ++;
    _pQueue[_nIn] = t;

    if(npIdx)
        *npIdx = _nIn;  //return the index of the pushed data
    _nIn  = (_nIn + 1)%_nCapacity;

    //Peek()의 초기화
    _nRef = 0;

    return _nCount;
}

template< class T > int KPtrQueue<T>::Pop(T& out)
{
    if(_nCount)
    {
        out 	= _pQueue[_nOut];
        _nOut 	= (_nOut+1)%_nCapacity;
    }

    //Peek()의 초기화
    _nRef = 0;

    return (_nCount ? --_nCount : -1);
}

template< class T > bool KPtrQueue<T>::Peek(T& out)
{
    int nRef 	= (_nOut+_nRef)%_nCapacity;

    if(_nRef < _nCount)
    {
        out = _pQueue[nRef];
        _nRef ++;
        return true;
    }

    //Peek()의 초기화
    _nRef = 0;

    return false;
}

template< class T > bool KPtrQueue<T>::Peek(int k,T& out)
{
    if(k < _nCount)
    {
        out = _pQueue[(_nOut + k)%_nCapacity];
        return true;
    }
    return false;
}

template< class T > void KPtrQueue<T>::Swap(const int& n1,const int& n2)
{
#ifdef _DEBUG
    assert(!(n1<0 || n2<0 || n1>=_nCapacity || n2>=_nCapacity));
#endif

    T Old = _pQueue[n1];
    _pQueue[n1] = _pQueue[n2];
    _pQueue[n2] = Old;
}

#endif
