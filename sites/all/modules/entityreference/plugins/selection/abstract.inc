<?php

/**
 * Abstraction of the selection logic of an entity reference field.
 *
 * Implementations that wish to provide an implementation of this should
 * register it using CTools' plugin system.
 */
interface EntityReference_SelectionHandler {
  /**
   * Factory function: create a new instance of this handler for a given field.
   *
   * @param $field
   *   A field datastructure.
   * @return EntityReferenceHandler
   */
  public static function getInstance($field, $instance = NULL, $entity_type = NULL, $entity = NULL);

  /**
   * Return a list of referencable entities.
   *
   * @return
   *   An array of referencable entities, which keys are entity ids and
   *   values (safe HTML) labels to be displayed to the user.
   */
  public function getReferencableEntities($match = NULL, $match_operator = 'CONTAINS', $limit = 0);

  /**
   * Count entities that are referencable by a given field.
   */
  public function countReferencableEntities($match = NULL, $match_operator = 'CONTAINS');

  /**
   * Validate that entities can be referenced by this field.
   *
   * @return
   *   An array of entity ids that are valid.
   */
  public function validateReferencableEntities(array $ids);

  /**
   * Give the handler a chance to alter the SelectQuery generated by EntityFieldQuery.
   */
  public function entityFieldQueryAlter(SelectQueryInterface $query);

  /**
   * Return the label of a given entity.
   */
  public function getLabel($entity);

  /**
   * Generate a settings form for this handler.
   */
  public static function settingsForm($field, $instance);
}

/**
 * A null implementation of EntityReference_SelectionHandler.
 */
class EntityReference_SelectionHandler_Broken implements EntityReference_SelectionHandler {
  public static function getInstance($field, $instance = NULL, $entity_type = NULL, $entity = NULL) {
    return new EntityReference_SelectionHandler_Broken($field, $instance, $entity_type, $entity);
  }

  protected function __construct($field, $instance) {
    $this->field = $field;
    $this->instance = $instance;
  }

  public static function settingsForm($field, $instance) {
    $form['selection_handler'] = array(
      '#markup' => t('The selected selection handler is broken.'),
    );
    return $form;
  }

  public function getReferencableEntities($match = NULL, $match_operator = 'CONTAINS', $limit = 0) {
    return array();
  }

  public function countReferencableEntities($match = NULL, $match_operator = 'CONTAINS') {
    return 0;
  }

  public function validateReferencableEntities(array $ids) {
    return array();
  }

  public function entityFieldQueryAlter(SelectQueryInterface $query) {}

  public function getLabel($entity) {
    return '';
  }
}
