#ifndef D_HalfFpBuildTime_H
#define D_HalfFpBuildTime_H

///////////////////////////////////////////////////////////////////////////////
//
//  HalfFpBuildTime is responsible for recording and reporting when
//  this project library was built
//
///////////////////////////////////////////////////////////////////////////////

class HalfFpBuildTime
  {
  public:
    explicit HalfFpBuildTime();
    virtual ~HalfFpBuildTime();
    
    const char* GetDateTime();

  private:
      
    const char* dateTime;

    HalfFpBuildTime(const HalfFpBuildTime&);
    HalfFpBuildTime& operator=(const HalfFpBuildTime&);

  };

#endif  // D_HalfFpBuildTime_H
