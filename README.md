Dining Philos
======
I had to do this as university labwork a while ago so I thought I might as well publish it. The task was to implement the problem of dining philosophers in C. We had to use the monitor concept which is implemented with mutual exclusion (mutex) from the pthread-library because C lacks a built-in monitor function. The communication from one philosopher to another was realized with condition variables(cond-vars). The realisation of thinking and eating should be done by to empty loops that go to a huge number(so it takes a while even on todays computers). A debug printout should be implemented as well to control everything is working as expected.

## Contact
* http://repat.de
* email: repat[at]repat[dot]de
* XMPP: repat@jabber.ccc.de
* Twitter: [repat123](https://twitter.com/repat123 "repat123 on twitter")

[![Flattr this git repo](http://api.flattr.com/button/flattr-badge-large.png)](https://flattr.com/submit/auto?user_id=repat&url=https://github.com/repat/scuttle2owncloud&title=scuttle2owncloud&language=&tags=github&category=software) 
