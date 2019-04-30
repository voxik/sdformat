/*
 * Copyright (C) 2019 Open Source Robotics Foundation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
*/

#include <gtest/gtest.h>

#include <ignition/math/Color.hh>
#include "sdf/Pbr.hh"

/////////////////////////////////////////////////
TEST(DOMPbr, Construction)
{
  sdf::Pbr pbr;
  EXPECT_EQ(nullptr, pbr.Workflow(sdf::PbrWorkflowType::METAL));
  EXPECT_EQ(nullptr, pbr.Workflow(sdf::PbrWorkflowType::SPECULAR));

  sdf::PbrWorkflow workflow;
  EXPECT_EQ(sdf::PbrWorkflowType::NONE, workflow.Type());
  EXPECT_EQ(std::string(), workflow.AlbedoMap());
  EXPECT_EQ(std::string(), workflow.NormalMap());
  EXPECT_EQ(sdf::NormalMapSpace::TANGENT, workflow.NormalMapType());
  EXPECT_EQ(std::string(), workflow.RoughnessMap());
  EXPECT_EQ(std::string(), workflow.MetalnessMap());
  EXPECT_DOUBLE_EQ(0.5, workflow.Roughness());
  EXPECT_DOUBLE_EQ(0.5, workflow.Metalness());
  EXPECT_EQ(std::string(), workflow.SpecularMap());
  EXPECT_EQ(std::string(), workflow.GlossinessMap());
  EXPECT_DOUBLE_EQ(0.0, workflow.Glossiness());
  EXPECT_EQ(std::string(), workflow.EnvironmentMap());
  EXPECT_EQ(std::string(), workflow.AmbientOcclusionMap());
}

/////////////////////////////////////////////////
TEST(DOMPbr, MoveConstructor)
{
  {
    // TODO(anyone) Fill PBR with meaningful data to be checked
    sdf::Pbr pbr;
    EXPECT_EQ(nullptr, pbr.Workflow(sdf::PbrWorkflowType::METAL));
    EXPECT_EQ(nullptr, pbr.Workflow(sdf::PbrWorkflowType::SPECULAR));

    sdf::Pbr pbr2(std::move(pbr));
    EXPECT_EQ(nullptr, pbr2.Workflow(sdf::PbrWorkflowType::METAL));
    EXPECT_EQ(nullptr, pbr2.Workflow(sdf::PbrWorkflowType::SPECULAR));
  }

  {
    // metal workflow
    sdf::PbrWorkflow workflow;
    workflow.SetType(sdf::PbrWorkflowType::METAL);
    workflow.SetAlbedoMap("metal_albedo_map.png");
    workflow.SetNormalMap("metal_normal_map.png", sdf::NormalMapSpace::TANGENT);
    workflow.SetEnvironmentMap("metal_env_map.png");
    workflow.SetAmbientOcclusionMap("metal_ambient_occlusion_map.png");
    workflow.SetRoughnessMap("roughness_map.png");
    workflow.SetMetalnessMap("metalness_map.png");
    workflow.SetRoughness(0.8);
    workflow.SetMetalness(0.3);

    sdf::PbrWorkflow workflow2(std::move(workflow));
    EXPECT_EQ(sdf::PbrWorkflowType::METAL, workflow2.Type());
    EXPECT_EQ("metal_albedo_map.png", workflow2.AlbedoMap());
    EXPECT_EQ("metal_normal_map.png", workflow2.NormalMap());
    EXPECT_EQ(sdf::NormalMapSpace::TANGENT, workflow2.NormalMapType());
    EXPECT_EQ("metal_env_map.png", workflow2.EnvironmentMap());
    EXPECT_EQ("metal_ambient_occlusion_map.png",
        workflow2.AmbientOcclusionMap());
    EXPECT_EQ("roughness_map.png", workflow2.RoughnessMap());
    EXPECT_EQ("metalness_map.png", workflow2.MetalnessMap());
    EXPECT_DOUBLE_EQ(0.8, workflow2.Roughness());
    EXPECT_DOUBLE_EQ(0.3, workflow2.Metalness());

    EXPECT_EQ(std::string(), workflow2.GlossinessMap());
    EXPECT_EQ(std::string(), workflow2.SpecularMap());
    EXPECT_DOUBLE_EQ(0.0, workflow2.Glossiness());
  }

  {
    // specular workflow
    sdf::PbrWorkflow workflow;
    workflow.SetType(sdf::PbrWorkflowType::SPECULAR);
    workflow.SetAlbedoMap("specular_albedo_map.png");
    workflow.SetNormalMap("specular_normal_map.png",
        sdf::NormalMapSpace::TANGENT);
    workflow.SetEnvironmentMap("specular_env_map.png");
    workflow.SetAmbientOcclusionMap("specular_ambient_occlusion_map.png");
    workflow.SetGlossinessMap("glossiness_map.png");
    workflow.SetSpecularMap("specular_map.png");
    workflow.SetGlossiness(0.1);

    sdf::PbrWorkflow workflow2(std::move(workflow));
    EXPECT_EQ(sdf::PbrWorkflowType::SPECULAR, workflow2.Type());
    EXPECT_EQ("specular_albedo_map.png", workflow2.AlbedoMap());
    EXPECT_EQ("specular_normal_map.png", workflow2.NormalMap());
    EXPECT_EQ(sdf::NormalMapSpace::TANGENT, workflow2.NormalMapType());
    EXPECT_EQ("specular_env_map.png", workflow2.EnvironmentMap());
    EXPECT_EQ("specular_ambient_occlusion_map.png",
        workflow2.AmbientOcclusionMap());
    EXPECT_EQ("specular_map.png", workflow2.SpecularMap());
    EXPECT_EQ("glossiness_map.png", workflow2.GlossinessMap());
    EXPECT_DOUBLE_EQ(0.1, workflow2.Glossiness());

    EXPECT_EQ(std::string(), workflow2.RoughnessMap());
    EXPECT_EQ(std::string(), workflow2.MetalnessMap());
    EXPECT_DOUBLE_EQ(0.5, workflow2.Roughness());
    EXPECT_DOUBLE_EQ(0.5, workflow2.Metalness());
  }
}

/////////////////////////////////////////////////
TEST(DOMPbr, MoveAssignmentOperator)
{
  {
    // TODO(anyone) Fill PBR with meaningful data to be checked
    sdf::Pbr pbr;
    EXPECT_EQ(nullptr, pbr.Workflow(sdf::PbrWorkflowType::METAL));
    EXPECT_EQ(nullptr, pbr.Workflow(sdf::PbrWorkflowType::SPECULAR));

    sdf::Pbr pbr2;
    pbr = std::move(pbr);
    EXPECT_EQ(nullptr, pbr2.Workflow(sdf::PbrWorkflowType::METAL));
    EXPECT_EQ(nullptr, pbr2.Workflow(sdf::PbrWorkflowType::SPECULAR));
  }

  {
    // metal workflow
    sdf::PbrWorkflow workflow;
    workflow.SetType(sdf::PbrWorkflowType::METAL);
    workflow.SetAlbedoMap("metal_albedo_map.png");
    workflow.SetNormalMap("metal_normal_map.png", sdf::NormalMapSpace::TANGENT);
    workflow.SetEnvironmentMap("metal_env_map.png");
    workflow.SetAmbientOcclusionMap("metal_ambient_occlusion_map.png");
    workflow.SetRoughnessMap("roughness_map.png");
    workflow.SetMetalnessMap("metalness_map.png");
    workflow.SetRoughness(0.8);
    workflow.SetMetalness(0.3);

    sdf::PbrWorkflow workflow2;
    workflow2 = std::move(workflow);
    EXPECT_EQ(sdf::PbrWorkflowType::METAL, workflow2.Type());
    EXPECT_EQ("metal_albedo_map.png", workflow2.AlbedoMap());
    EXPECT_EQ("metal_normal_map.png", workflow2.NormalMap());
    EXPECT_EQ(sdf::NormalMapSpace::TANGENT, workflow2.NormalMapType());
    EXPECT_EQ("metal_env_map.png", workflow2.EnvironmentMap());
    EXPECT_EQ("metal_ambient_occlusion_map.png",
        workflow2.AmbientOcclusionMap());
    EXPECT_EQ("roughness_map.png", workflow2.RoughnessMap());
    EXPECT_EQ("metalness_map.png", workflow2.MetalnessMap());
    EXPECT_DOUBLE_EQ(0.8, workflow2.Roughness());
    EXPECT_DOUBLE_EQ(0.3, workflow2.Metalness());

    EXPECT_EQ(std::string(), workflow2.GlossinessMap());
    EXPECT_EQ(std::string(), workflow2.SpecularMap());
    EXPECT_DOUBLE_EQ(0.0, workflow2.Glossiness());
  }

  {
    // specular workflow
    sdf::PbrWorkflow workflow;
    workflow.SetType(sdf::PbrWorkflowType::SPECULAR);
    workflow.SetAlbedoMap("specular_albedo_map.png");
    workflow.SetNormalMap("specular_normal_map.png",
        sdf::NormalMapSpace::TANGENT);
    workflow.SetEnvironmentMap("specular_env_map.png");
    workflow.SetAmbientOcclusionMap("specular_ambient_occlusion_map.png");
    workflow.SetGlossinessMap("glossiness_map.png");
    workflow.SetSpecularMap("specular_map.png");
    workflow.SetGlossiness(0.1);

    sdf::PbrWorkflow workflow2;
    workflow2 = std::move(workflow);
    EXPECT_EQ(sdf::PbrWorkflowType::SPECULAR, workflow2.Type());
    EXPECT_EQ("specular_albedo_map.png", workflow2.AlbedoMap());
    EXPECT_EQ("specular_normal_map.png", workflow2.NormalMap());
    EXPECT_EQ(sdf::NormalMapSpace::TANGENT, workflow2.NormalMapType());
    EXPECT_EQ("specular_env_map.png", workflow2.EnvironmentMap());
    EXPECT_EQ("specular_ambient_occlusion_map.png",
        workflow2.AmbientOcclusionMap());
    EXPECT_EQ("specular_map.png", workflow2.SpecularMap());
    EXPECT_EQ("glossiness_map.png", workflow2.GlossinessMap());
    EXPECT_DOUBLE_EQ(0.1, workflow2.Glossiness());

    EXPECT_EQ(std::string(), workflow2.RoughnessMap());
    EXPECT_EQ(std::string(), workflow2.MetalnessMap());
    EXPECT_DOUBLE_EQ(0.5, workflow2.Roughness());
    EXPECT_DOUBLE_EQ(0.5, workflow2.Metalness());
  }
}



/////////////////////////////////////////////////
TEST(DOMPbr, CopyConstructor)
{
  {
    // TODO(anyone) Fill PBR with meaningful data to be checked
    sdf::Pbr pbr;
    EXPECT_EQ(nullptr, pbr.Workflow(sdf::PbrWorkflowType::METAL));
    EXPECT_EQ(nullptr, pbr.Workflow(sdf::PbrWorkflowType::SPECULAR));

    sdf::Pbr pbr2(pbr);
    EXPECT_EQ(nullptr, pbr2.Workflow(sdf::PbrWorkflowType::METAL));
    EXPECT_EQ(nullptr, pbr2.Workflow(sdf::PbrWorkflowType::SPECULAR));
  }

  {
    // metal workflow
    sdf::PbrWorkflow workflow;
    workflow.SetType(sdf::PbrWorkflowType::METAL);
    workflow.SetAlbedoMap("metal_albedo_map.png");
    workflow.SetNormalMap("metal_normal_map.png");
    workflow.SetEnvironmentMap("metal_env_map.png");
    workflow.SetAmbientOcclusionMap("metal_ambient_occlusion_map.png");
    workflow.SetRoughnessMap("roughness_map.png");
    workflow.SetMetalnessMap("metalness_map.png");
    workflow.SetRoughness(0.8);
    workflow.SetMetalness(0.3);

    sdf::PbrWorkflow workflow2(workflow);
    EXPECT_EQ(sdf::PbrWorkflowType::METAL, workflow2.Type());
    EXPECT_EQ("metal_albedo_map.png", workflow2.AlbedoMap());
    EXPECT_EQ("metal_normal_map.png", workflow2.NormalMap());
    EXPECT_EQ(sdf::NormalMapSpace::TANGENT, workflow2.NormalMapType());
    EXPECT_EQ("metal_env_map.png", workflow2.EnvironmentMap());
    EXPECT_EQ("metal_ambient_occlusion_map.png",
        workflow2.AmbientOcclusionMap());
    EXPECT_EQ("roughness_map.png", workflow2.RoughnessMap());
    EXPECT_EQ("metalness_map.png", workflow2.MetalnessMap());
    EXPECT_DOUBLE_EQ(0.8, workflow2.Roughness());
    EXPECT_DOUBLE_EQ(0.3, workflow2.Metalness());

    EXPECT_EQ(std::string(), workflow2.GlossinessMap());
    EXPECT_EQ(std::string(), workflow2.SpecularMap());
    EXPECT_DOUBLE_EQ(0.0, workflow2.Glossiness());
  }

  {
    // specular workflow
    sdf::PbrWorkflow workflow;
    workflow.SetType(sdf::PbrWorkflowType::SPECULAR);
    workflow.SetAlbedoMap("specular_albedo_map.png");
    workflow.SetNormalMap("specular_normal_map.png");
    workflow.SetEnvironmentMap("specular_env_map.png");
    workflow.SetAmbientOcclusionMap("specular_ambient_occlusion_map.png");
    workflow.SetGlossinessMap("glossiness_map.png");
    workflow.SetSpecularMap("specular_map.png");
    workflow.SetGlossiness(0.1);

    sdf::PbrWorkflow workflow2(workflow);
    EXPECT_EQ(sdf::PbrWorkflowType::SPECULAR, workflow2.Type());
    EXPECT_EQ("specular_albedo_map.png", workflow2.AlbedoMap());
    EXPECT_EQ("specular_normal_map.png", workflow2.NormalMap());
    EXPECT_EQ(sdf::NormalMapSpace::TANGENT, workflow2.NormalMapType());
    EXPECT_EQ("specular_env_map.png", workflow2.EnvironmentMap());
    EXPECT_EQ("specular_ambient_occlusion_map.png",
        workflow2.AmbientOcclusionMap());
    EXPECT_EQ("specular_map.png", workflow2.SpecularMap());
    EXPECT_EQ("glossiness_map.png", workflow2.GlossinessMap());
    EXPECT_DOUBLE_EQ(0.1, workflow2.Glossiness());

    EXPECT_EQ(std::string(), workflow2.RoughnessMap());
    EXPECT_EQ(std::string(), workflow2.MetalnessMap());
    EXPECT_DOUBLE_EQ(0.5, workflow2.Roughness());
    EXPECT_DOUBLE_EQ(0.5, workflow2.Metalness());
  }
}

/////////////////////////////////////////////////
TEST(DOMPbr, AssignmentOperator)
{
  {
    // TODO(anyone) Fill PBR with meaningful data to be checked
    sdf::Pbr pbr;
    EXPECT_EQ(nullptr, pbr.Workflow(sdf::PbrWorkflowType::METAL));
    EXPECT_EQ(nullptr, pbr.Workflow(sdf::PbrWorkflowType::SPECULAR));

    sdf::Pbr pbr2;
    pbr2 = pbr;
    EXPECT_EQ(nullptr, pbr2.Workflow(sdf::PbrWorkflowType::METAL));
    EXPECT_EQ(nullptr, pbr2.Workflow(sdf::PbrWorkflowType::SPECULAR));
  }

  {
    // metal workflow
    sdf::PbrWorkflow workflow;
    workflow.SetType(sdf::PbrWorkflowType::METAL);
    workflow.SetAlbedoMap("metal_albedo_map.png");
    workflow.SetNormalMap("metal_normal_map.png");
    workflow.SetEnvironmentMap("metal_env_map.png");
    workflow.SetAmbientOcclusionMap("metal_ambient_occlusion_map.png");
    workflow.SetRoughnessMap("roughness_map.png");
    workflow.SetMetalnessMap("metalness_map.png");
    workflow.SetRoughness(0.8);
    workflow.SetMetalness(0.3);

    sdf::PbrWorkflow workflow2;
    workflow2 = workflow;
    EXPECT_EQ(sdf::PbrWorkflowType::METAL, workflow2.Type());
    EXPECT_EQ("metal_albedo_map.png", workflow2.AlbedoMap());
    EXPECT_EQ("metal_normal_map.png", workflow2.NormalMap());
    EXPECT_EQ("metal_env_map.png", workflow2.EnvironmentMap());
    EXPECT_EQ("metal_ambient_occlusion_map.png",
        workflow2.AmbientOcclusionMap());
    EXPECT_EQ("roughness_map.png", workflow2.RoughnessMap());
    EXPECT_EQ("metalness_map.png", workflow2.MetalnessMap());
    EXPECT_DOUBLE_EQ(0.8, workflow2.Roughness());
    EXPECT_DOUBLE_EQ(0.3, workflow2.Metalness());

    EXPECT_EQ(std::string(), workflow2.GlossinessMap());
    EXPECT_EQ(std::string(), workflow2.SpecularMap());
    EXPECT_DOUBLE_EQ(0.0, workflow2.Glossiness());
  }

  {
    // specular workflow
    sdf::PbrWorkflow workflow;
    workflow.SetType(sdf::PbrWorkflowType::SPECULAR);
    workflow.SetAlbedoMap("specular_albedo_map.png");
    workflow.SetNormalMap("specular_normal_map.png");
    workflow.SetEnvironmentMap("specular_env_map.png");
    workflow.SetAmbientOcclusionMap("specular_ambient_occlusion_map.png");
    workflow.SetGlossinessMap("glossiness_map.png");
    workflow.SetSpecularMap("specular_map.png");
    workflow.SetGlossiness(0.1);

    sdf::PbrWorkflow workflow2(workflow);
    EXPECT_EQ(sdf::PbrWorkflowType::SPECULAR, workflow2.Type());
    EXPECT_EQ("specular_albedo_map.png", workflow2.AlbedoMap());
    EXPECT_EQ("specular_normal_map.png", workflow2.NormalMap());
    EXPECT_EQ("specular_env_map.png", workflow2.EnvironmentMap());
    EXPECT_EQ("specular_ambient_occlusion_map.png",
        workflow2.AmbientOcclusionMap());
    EXPECT_EQ("specular_map.png", workflow2.SpecularMap());
    EXPECT_EQ("glossiness_map.png", workflow2.GlossinessMap());
    EXPECT_DOUBLE_EQ(0.1, workflow2.Glossiness());

    EXPECT_EQ(std::string(), workflow2.RoughnessMap());
    EXPECT_EQ(std::string(), workflow2.MetalnessMap());
    EXPECT_DOUBLE_EQ(0.5, workflow2.Roughness());
    EXPECT_DOUBLE_EQ(0.5, workflow2.Metalness());
  }
}

/////////////////////////////////////////////////
TEST(DOMPbr, CopyAssignmentAfterMove)
{
  {
    sdf::Pbr pbr1;
    sdf::Pbr pbr2;

    // This is similar to what std::swap does except it uses std::move for each
    // assignment
    sdf::Pbr tmp = std::move(pbr1);
    pbr1 = pbr2;
    pbr2 = tmp;

    EXPECT_EQ(pbr1.Workflow(sdf::PbrWorkflowType::METAL),
        pbr2.Workflow(sdf::PbrWorkflowType::METAL));
    EXPECT_EQ(pbr1.Workflow(sdf::PbrWorkflowType::SPECULAR),
        pbr2.Workflow(sdf::PbrWorkflowType::SPECULAR));
  }

  {
    sdf::PbrWorkflow workflow1;
    workflow1.SetType(sdf::PbrWorkflowType::METAL);

    sdf::PbrWorkflow workflow2;
    workflow2.SetType(sdf::PbrWorkflowType::SPECULAR);

    // This is similar to what std::swap does except it uses std::move for each
    // assignment
    sdf::PbrWorkflow tmp = std::move(workflow1);
    workflow1 = workflow2;
    workflow2 = tmp;

    EXPECT_EQ(sdf::PbrWorkflowType::SPECULAR, workflow1.Type());
    EXPECT_EQ(sdf::PbrWorkflowType::METAL, workflow2.Type());
  }
}

/////////////////////////////////////////////////
TEST(DOMPbr, Set)
{
  {
    // metal workflow
    sdf::PbrWorkflow workflow;
    workflow.SetType(sdf::PbrWorkflowType::METAL);
    EXPECT_EQ(sdf::PbrWorkflowType::METAL, workflow.Type());

    workflow.SetAlbedoMap("metal_albedo_map.png");
    EXPECT_EQ("metal_albedo_map.png", workflow.AlbedoMap());

    workflow.SetNormalMap("metal_normal_map.png");
    EXPECT_EQ("metal_normal_map.png", workflow.NormalMap());

    workflow.SetEnvironmentMap("metal_env_map.png");
    EXPECT_EQ("metal_env_map.png", workflow.EnvironmentMap());

    workflow.SetAmbientOcclusionMap("metal_ambient_occlusion_map.png");
    EXPECT_EQ("metal_ambient_occlusion_map.png",
        workflow.AmbientOcclusionMap());

    workflow.SetRoughnessMap("roughness_map.png");
    EXPECT_EQ("roughness_map.png", workflow.RoughnessMap());

    workflow.SetMetalnessMap("metalness_map.png");
    EXPECT_EQ("metalness_map.png", workflow.MetalnessMap());

    workflow.SetRoughness(0.8);
    EXPECT_DOUBLE_EQ(0.8, workflow.Roughness());

    workflow.SetMetalness(0.3);
    EXPECT_DOUBLE_EQ(0.3, workflow.Metalness());

    EXPECT_EQ(std::string(), workflow.GlossinessMap());
    EXPECT_EQ(std::string(), workflow.SpecularMap());
    EXPECT_DOUBLE_EQ(0.0, workflow.Glossiness());
  }

  {
    // specular workflow
    sdf::PbrWorkflow workflow;
    workflow.SetType(sdf::PbrWorkflowType::SPECULAR);
    EXPECT_EQ(sdf::PbrWorkflowType::SPECULAR, workflow.Type());

    workflow.SetAlbedoMap("specular_albedo_map.png");
    EXPECT_EQ("specular_albedo_map.png", workflow.AlbedoMap());

    workflow.SetNormalMap("specular_normal_map.png",
        sdf::NormalMapSpace::OBJECT);
    EXPECT_EQ("specular_normal_map.png", workflow.NormalMap());
    EXPECT_EQ(sdf::NormalMapSpace::OBJECT, workflow.NormalMapType());

    workflow.SetEnvironmentMap("specular_env_map.png");
    EXPECT_EQ("specular_env_map.png", workflow.EnvironmentMap());

    workflow.SetAmbientOcclusionMap("specular_ambient_occlusion_map.png");
    EXPECT_EQ("specular_ambient_occlusion_map.png",
        workflow.AmbientOcclusionMap());

    workflow.SetGlossinessMap("glossiness_map.png");
    EXPECT_EQ("glossiness_map.png", workflow.GlossinessMap());

    workflow.SetSpecularMap("specular_map.png");
    EXPECT_EQ("specular_map.png", workflow.SpecularMap());

    workflow.SetGlossiness(0.1);
    EXPECT_DOUBLE_EQ(0.1, workflow.Glossiness());

    EXPECT_EQ(std::string(), workflow.RoughnessMap());
    EXPECT_EQ(std::string(), workflow.MetalnessMap());
    EXPECT_DOUBLE_EQ(0.5, workflow.Roughness());
    EXPECT_DOUBLE_EQ(0.5, workflow.Metalness());
  }
}

/////////////////////////////////////////////////
TEST(DOMPbr, InvalidSdf)
{
  sdf::Pbr pbr;
  sdf::ElementPtr elem(new sdf::Element());
  elem->SetName("bad");
  sdf::Errors errors = pbr.Load(elem);
  EXPECT_EQ(sdf::ErrorCode::ELEMENT_INCORRECT_TYPE, errors[0].Code());

  sdf::PbrWorkflow workflow;
  sdf::ElementPtr workflowElem(new sdf::Element());
  workflowElem->SetName("bad");
  sdf::Errors workflowErrors = workflow.Load(workflowElem);
  EXPECT_EQ(sdf::ErrorCode::ELEMENT_INCORRECT_TYPE, workflowErrors[0].Code());
}