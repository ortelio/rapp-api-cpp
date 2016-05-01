#!/usr/bin/env python


# Copyright 2016 RAPP

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

    #http://www.apache.org/licenses/LICENSE-2.0

# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

# Authors: Konstantinos Panayiotou
# contact: klpanagi@gmail.com


## @file RappCloud/CloudServices/OntologyIsSubsuperclass.py
#
#  @copyright Rapp Projecty EU 2016
#  @author Konstantinos Panayiotou, [klpanagi@gmail.com]
#


from Service import *
from RappCloud.Objects import (
    File,
    Payload
    )


class OntologyIsSubsuperclass(Service):
  """ OntologyIsSubsuperclass Cloud Service class """

  def __init__(self, **kwargs):
    """!
    Constructor

    @param **kwargs - Keyword arguments. Apply values to the request attributes.
      - @ref parent_class
      - @ref child_class
      - @ref recursive
    """

    # Cloud Service request arguments
    # -------------------------------------------------------------
    ## The parent class name.
    self.parent_class = ''
    ## The child class name.
    self.child_class = ''
    ## True if a recursive procedure will be used (true/false).
    self.recursive = False
    # -------------------------------------------------------------

    super(OntologyIsSubsuperclass, self).__init__(
        svcname='ontology_is_subsuperclass_of',
        **kwargs
        )


  def _make_payload(self):
    """ Make request payload object """
    return Payload(
        parent_class=self.parent_class,
        child_class=self.child_class,
        recursive=self.recursive
        )


  def _make_files(self):
    """ Create array of file object(s) """
    return []
