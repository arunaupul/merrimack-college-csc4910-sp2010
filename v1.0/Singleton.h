#ifndef _SINGLETON_H_
#define _SINGLETON_H_

class Singleton
{
public:
	static Singleton * Instance();
protected:
	Singleton();
	virtual ~Singleton();
	Singleton( const Singleton & );
	Singleton & operator=( const Singleton & );
private:
	static Singleton * m_instance;
};

#endif /* _SINGLETON_H_ */