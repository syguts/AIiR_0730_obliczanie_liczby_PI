from django.conf.urls import patterns, include, url
from django.contrib import admin

urlpatterns = patterns('',
    # Examples:
    # url(r'^$', 'appI.views.home', name='home'),
    # url(r'^blog/', include('blog.urls')),
    url(r'^PI/$', 'PI.views.index'),
    url(r'^PI/(?P<PI_id>\d+)/$', 'PI.views.detail'),
    url(r'^PI/(?P<PI_id>\d+)/results/$', 'PI.views.results'),
    url(r'^PI/(?P<PI_id>\d+)/vote/$', 'PI.views.vote'),
    url(r'^admin/', include(admin.site.urls)),
)
