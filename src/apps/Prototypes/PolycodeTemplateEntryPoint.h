//
// Polycode template. Write your code here.
//

#import <PolycodeView.h>
#include <Polycode.h>

class AppCore;

class PolycodeTemplateEntryPoint {
public:
    PolycodeTemplateEntryPoint(PolycodeView *view);
    ~PolycodeTemplateEntryPoint();
    
    bool Update();
    
private:
    AppCore *auntCore;
};