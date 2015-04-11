from django.conf.urls import patterns, include, url
from django.contrib import admin


urlpatterns = patterns('',
    # Examples:
    # url(r'^$', 'appI.views.home', name='home'),
    # url(r'^blog/', include('blog.urls')),
    url(r'^$', 'PI.views.index'),
    #url(r'^PI/$', 'PI.views.indexPI'),
    #url(r'^PI/(?P<PI_id>\d+)/$', 'PI.views.detail'),
    #url(r'^PI/(?P<PI_id>\d+)/results/$', 'PI.views.results'),
    #url(r'^PI/(?P<PI_id>\d+)/vote/$', 'PI.views.vote'),
    url(r'^admin/', include(admin.site.urls)),
    url(r'^register/$', 'PI.views.register', name='register'),
    url(r'^login/$', 'PI.views.user_login', name='login'),
    url(r'^logout/$', 'PI.views.user_logout', name='logout'),
    )
