from django.conf.urls import patterns, include, url
from django.contrib import admin

urlpatterns = patterns('',
    # Examples:
    # url(r'^$', 'PI.views.home', name='home'),
    # url(r'^blog/', include('blog.urls')),
    url(r'^$', 'PI2.views.index'),
    url(r'^admin/', include(admin.site.urls)),
    url(r'^register/$', 'PI2.views.register', name='register'),
    url(r'^login/$', 'PI2.views.user_login', name='login'),
    url(r'^logout/$', 'PI2.views.user_logout', name='logout'),
)





