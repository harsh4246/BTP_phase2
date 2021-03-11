#ifndef TARGET_H
#define TARGET_H




class target
{
    public:
        friend class vehicle;
        target( double* position, double tolerance);
        double * getPosition();

    protected:

    private:

        double position[3];
        double tolerance;

};

#endif // TARGET_H
